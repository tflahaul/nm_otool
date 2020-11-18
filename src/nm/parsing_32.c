/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_32.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:06:19 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/29 16:28:56 by thflahau         ###   ########.fr       */
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
#include <string.h>
#include <stdint.h>

static int			parse_symtab(struct machobj *mach, void const *off)
{
	struct symtab_command	symtab;
	struct nlist		symbol;
	struct nlist		*offset;

	memcpy(&symtab, off, sizeof(struct symtab_command));
	if (mach->magic == MH_CIGAM)
		swap_symtab_command(&symtab, NXHostByteOrder());
	if (symtab.cmdsize != sizeof(struct symtab_command))
		return (-EXIT_FAILURE);
	mach->strtab = (void *)((uintptr_t)mach->object.head + symtab.stroff);
	offset = (void *)((uintptr_t)mach->object.head + symtab.symoff);
	for (register uint32_t index = 0; index < symtab.nsyms; ++index) {
		if (__is_readable(&(mach->object), &(offset[index]), sizeof(struct nlist))) {
			memcpy(&symbol, &(offset[index]), sizeof(struct nlist));
			if (mach->magic == MH_CIGAM)
				swap_nlist(&symbol, 1, NXHostByteOrder());
			if (insert_symbol(mach, (void *)(&symbol)) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}

static int			parse_segment(struct machobj *mach, void const *off)
{
	struct segment_command	segment;
	struct section		section;
	struct section		*secptr;

	memcpy(&segment, off, sizeof(struct segment_command));
	if (mach->magic == MH_CIGAM)
		swap_segment_command(&segment, NXHostByteOrder());
	secptr = (struct section *)((uintptr_t)off + sizeof(struct segment_command));
	for (register uint32_t index = 0; index < segment.nsects; ++index) {
		if (__is_readable(&(mach->object), &(secptr[index]), sizeof(struct section))) {
			memcpy(&section, &(secptr[index]), sizeof(struct section));
			if (mach->magic == MH_CIGAM)
				swap_section(&section, 1, NXHostByteOrder());
			if (push_section(&(mach->sections_list), &section) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}

static int			parse_load_command(struct machobj *mach, void const *off)
{
	struct load_command	loadcmd;

	memcpy(&loadcmd, off, sizeof(struct load_command));
	if (mach->magic == MH_CIGAM)
		swap_load_command(&loadcmd, NXHostByteOrder());
	if ((uintptr_t)off + loadcmd.cmdsize <= __end_addr(&(mach->object))) {
		if (loadcmd.cmd == LC_SYMTAB) {
			if (parse_symtab(mach, off) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		} else if (loadcmd.cmd == LC_SEGMENT) {
			if (parse_segment(mach, off) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int				get_symbols_32(struct machobj *mach)
{
	struct mach_header	header;
	struct load_command	*ptr;

	if (mach->object.length < sizeof(struct mach_header))
		return (-EXIT_FAILURE);
	memcpy(&header, mach->object.head, sizeof(struct mach_header));
	if (mach->magic == MH_CIGAM)
		swap_mach_header(&header, NXHostByteOrder());
	ptr = (struct load_command *)((uintptr_t)mach->object.head + sizeof(struct mach_header));
	for (uint32_t index = 0; index < header.ncmds; ++index) {
		if (__is_readable(&(mach->object), ptr, sizeof(struct load_command)) && ptr->cmdsize > 0) {
			if (parse_load_command(mach, ptr) != EXIT_SUCCESS) {
				free_sections_list(mach->sections_list);
				btree_free(mach->symbols_root);
				return (-EXIT_FAILURE);
			}
			ptr = (void *)((uintptr_t)ptr + ptr->cmdsize);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}
