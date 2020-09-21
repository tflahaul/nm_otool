/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_x86_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:06:19 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/21 11:46:15 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/errors.h"
#include "../../include/bytes.h"
#include "../../include/parsing.h"
#include "../../include/sections.h"
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/swap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int			push_symbol(struct symbol **head, struct nlist_64 *sym)
{
	struct symbol		*node;

	if (sym->n_type & N_STAB)
		return (EXIT_SUCCESS);
	if ((node = (struct symbol *)malloc(sizeof(struct symbol))) == NULL)
		return (-EXIT_FAILURE);
	node->value = sym->n_value;
	node->stridx = sym->n_un.n_strx;
	node->type = (uint32_t)sym->n_type;
	node->sectid = (uint32_t)sym->n_sect;
	node->next = (*head == NULL) ? NULL : *head;
	*head = node;
	return (EXIT_SUCCESS);
}

static int			parse_symtab(struct file *f, struct machobj *m, void const *ptr)
{
	struct symtab_command	symtab;
	struct nlist_64		symbol;
	struct nlist_64		*offset;

	memcpy(&symtab, ptr, sizeof(struct symtab_command));
	if (m->magic == MH_CIGAM_64)
		swap_symtab_command(&symtab, NXHostByteOrder());
	if (symtab.cmdsize != sizeof(struct symtab_command))
		return (-EXIT_FAILURE);
	m->strtab = (void *)((uintptr_t)m->offset + symtab.stroff);
	offset = (void *)((uintptr_t)m->offset + symtab.symoff);
	for (register uint32_t index = 0; index < symtab.nsyms; ++index) {
		if (__readable(f, &(offset[index]), struct nlist_64) == TRUE) {
			memcpy(&symbol, &(offset[index]), sizeof(struct nlist_64));
			if (m->magic == MH_CIGAM_64)
				swap_nlist_64(&symbol, 1, NXHostByteOrder());
			if (push_symbol(&(m->symbols_list), &symbol) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}

static int			parse_segment(struct file *f, struct machobj *m, void const *ptr)
{
	struct segment_command_64	segment;
	struct section_64		section;
	struct section_64		*secptr;

	memcpy(&segment, ptr, sizeof(struct segment_command_64));
	if (m->magic == MH_CIGAM_64)
		swap_segment_command_64(&segment, NXHostByteOrder());
	secptr = (struct section_64 *)((uintptr_t)ptr + sizeof(struct segment_command_64));
	for (register uint32_t idx = 0; idx < segment.nsects; ++idx) {
		if (__readable(f, &(secptr[idx]), struct section_64) == TRUE) {
			memcpy(&section, &(secptr[idx]), sizeof(struct section_64));
			if (m->magic == MH_CIGAM_64)
				swap_section_64(&section, 1, NXHostByteOrder());
			if (push_section(&(m->sections_list), &section) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}

static int			parse_load_command(struct file *f, struct machobj *mach, void *ptr)
{
	struct load_command	loadcmd;

	memcpy(&loadcmd, ptr, sizeof(struct load_command));
	if (mach->magic == MH_CIGAM_64)
		swap_load_command(&loadcmd, NXHostByteOrder());
	if ((uintptr_t)ptr + loadcmd.cmdsize <= (uintptr_t)f->head + f->length) {
		if (loadcmd.cmd == LC_SYMTAB) {
			if (parse_symtab(f, mach, ptr) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else if (loadcmd.cmd == LC_SEGMENT_64) {
			if (parse_segment(f, mach, ptr) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int				get_symbols_x86_64(struct file *f, struct machobj *mach)
{
	struct mach_header_64	header;
	void			*ptr;

	if (__readable(f, mach->offset, struct mach_header_64) == TRUE) {
		memcpy(&header, mach->offset, sizeof(struct mach_header_64));
		if (mach->magic == MH_CIGAM_64)
			swap_mach_header_64(&header, NXHostByteOrder());
		ptr = (void *)((uintptr_t)mach->offset + sizeof(struct mach_header_64));
		for (register uint32_t index = 0; index < header.ncmds; ++index) {
			if (__readable(f, ptr, struct load_command) && ((struct load_command *)ptr)->cmdsize > 0) {
				if (parse_load_command(f, mach, ptr) != EXIT_SUCCESS) {
					free_sections_list(mach->sections_list);
					return (-EXIT_FAILURE);
				}
				ptr = (void *)((uintptr_t)ptr + ((struct load_command *)ptr)->cmdsize);
			} else { return (-EXIT_FAILURE); }
		}
	}
	return (EXIT_SUCCESS);
}
