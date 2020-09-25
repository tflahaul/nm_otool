/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_x86_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:06:19 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/25 17:01:57 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/bytes.h"
#include "../../include/errors.h"
#include "../../include/sections.h"
#if defined __APPLE__
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/swap.h>
#else
# error "Systems other than macOS are not supported"
#endif /* __APPLE__ */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int			parse_symtab(struct machobj *mach, void const *off)
{
	struct symtab_command	symtab;
	struct nlist_64		symbol;
	struct nlist_64		*offset;

	memcpy(&symtab, off, sizeof(struct symtab_command));
	if (mach->magic == MH_CIGAM_64)
		swap_symtab_command(&symtab, NXHostByteOrder());
	if (symtab.cmdsize != sizeof(struct symtab_command))
		return (-EXIT_FAILURE);
	mach->strtab = (void *)((uintptr_t)mach->object.head + symtab.stroff);
	offset = (void *)((uintptr_t)mach->object.head + symtab.symoff);
	for (register uint32_t index = 0; index < symtab.nsyms; ++index) {
		if (__readable(&(mach->object), &(offset[index]), struct nlist_64) == TRUE) {
			memcpy(&symbol, &(offset[index]), sizeof(struct nlist_64));
			if (mach->magic == MH_CIGAM_64)
				swap_nlist_64(&symbol, 1, NXHostByteOrder());
			if (insert_symbol(mach, &symbol) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}

static int			parse_segment(struct machobj *mach, void const *off)
{
	struct segment_command_64	segment;
	struct section_64		section;
	struct section_64		*secptr;

	memcpy(&segment, off, sizeof(struct segment_command_64));
	if (mach->magic == MH_CIGAM_64)
		swap_segment_command_64(&segment, NXHostByteOrder());
	secptr = (struct section_64 *)((uintptr_t)off + sizeof(struct segment_command_64));
	for (register uint32_t index = 0; index < segment.nsects; ++index) {
		if (__readable(&(mach->object), &(secptr[index]), struct section_64) == TRUE) {
			memcpy(&section, &(secptr[index]), sizeof(struct section_64));
			if (mach->magic == MH_CIGAM_64)
				swap_section_64(&section, 1, NXHostByteOrder());
			if (push_section_64(&(mach->sections_list), &section) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}

static int			parse_load_command(struct machobj *mach, void *off)
{
	struct load_command	loadcmd;

	memcpy(&loadcmd, off, sizeof(struct load_command));
	if (mach->magic == MH_CIGAM_64)
		swap_load_command(&loadcmd, NXHostByteOrder());
	if ((uintptr_t)off + loadcmd.cmdsize <= __end_addr(&(mach->object))) {
		if (loadcmd.cmd == LC_SYMTAB) {
			if (parse_symtab(mach, off) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else if (loadcmd.cmd == LC_SEGMENT_64) {
			if (parse_segment(mach, off) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int				get_symbols_x86_64(struct machobj *mach)
{
	struct mach_header_64	header;
	struct load_command	*ptr;

	if (__readable(&(mach->object), mach->object.head, struct mach_header_64) == TRUE) {
		memcpy(&header, mach->object.head, sizeof(struct mach_header_64));
		if (mach->magic == MH_CIGAM_64)
			swap_mach_header_64(&header, NXHostByteOrder());
		ptr = (struct load_command *)((uintptr_t)mach->object.head + sizeof(struct mach_header_64));
		for (register uint32_t index = 0; index < header.ncmds; ++index) {
			if (__readable(&(mach->object), ptr, struct load_command) && ptr->cmdsize > 0) {
				if (parse_load_command(mach, ptr) != EXIT_SUCCESS) {
					free_sections_list(mach->sections_list);
					btree_free(mach->symbols_root);
					return (-EXIT_FAILURE);
				}
				ptr = (void *)((uintptr_t)ptr + ptr->cmdsize);
			} else { return (-EXIT_FAILURE); }
		}
	}
	return (EXIT_SUCCESS);
}
