/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_i386.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:06:19 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/18 16:20:42 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/errors.h"
#include "../../include/memory.h"
#include "../../include/parsing.h"
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/swap.h>
#include <string.h>
#include <stdint.h>

static int			parse_segment(struct file *f, struct machobj *m, void const *ptr)
{
	struct segment_command	segment;
	struct section		section;
	struct section		*secptr;

	memcpy(&segment, ptr, sizeof(struct segment_command));
	if (m->magic == MH_CIGAM)
		swap_segment_command(&segment, NXHostByteOrder());
	secptr = (struct section *)((uintptr_t)ptr + sizeof(struct segment_command));
	for (register uint32_t index = 0; index < segment.nsects; ++index) {
		if (__readable(f, &(secptr[index]), struct section) == TRUE) {
			memcpy(&section, &(secptr[index]), sizeof(struct section));
			if (m->magic == MH_CIGAM)
				swap_section(&section, 1, NXHostByteOrder());
			push_section(&(m->sections_list), &section, index + 1);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}

static int			parse_load_command(struct file *f, struct machobj *mach, void *ptr)
{
	struct load_command	loadcmd;

	memcpy(&loadcmd, ptr, sizeof(struct load_command));
	if (mach->magic == MH_CIGAM)
		swap_load_command(&loadcmd, NXHostByteOrder());
	if ((uintptr_t)ptr + loadcmd.cmdsize <= (uintptr_t)f->head + f->length) {
		if (loadcmd.cmd == LC_SYMTAB) {
//			if (parse_symtab(f, mach, ptr) != EXIT_SUCCESS)
//				return (-EXIT_FAILURE);
		} else if (loadcmd.cmd == LC_SEGMENT) {
			if (parse_segment(f, mach, ptr) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int				get_symbols_i386(struct file *f, struct machobj *mach)
{
	struct mach_header	header;
	void			*ptr;

	if (__readable(f, mach->offset, struct mach_header) == TRUE) {
		memcpy(&header, mach->offset, sizeof(struct mach_header));
		if (mach->magic == MH_CIGAM)
			swap_mach_header(&header, NXHostByteOrder());
		ptr = (void *)((uintptr_t)mach->offset + sizeof(struct mach_header));
		for (uint32_t index = 0; index < header.ncmds; ++index) {
			if (__readable(f, ptr, struct load_command) && ((struct load_command *)ptr)->cmdsize > 0) {
				parse_load_command(f, mach, ptr);
				ptr = (void *)((uintptr_t)ptr + ((struct load_command *)ptr)->cmdsize);
			} else { return (-EXIT_FAILURE); }
		}
	}
	return (EXIT_SUCCESS);
}
