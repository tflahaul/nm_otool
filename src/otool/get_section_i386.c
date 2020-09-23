/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_i386.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:37:20 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/23 19:44:43 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/errors.h"
#include "../../include/bytes.h"
#include "../../include/sections.h"
#include "../../include/otool.h"
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/swap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int			parse_segment(struct file *f, struct machobj *m, void const *ptr)
{
	struct segment_command	segment;
	struct section		section;
	struct section		*secptr;

	memcpy(&segment, ptr, sizeof(struct segment_command));
	if (m->magic == MH_CIGAM)
		swap_segment_command(&segment, NXHostByteOrder());
	if (strcmp(segment.segname, SEG_TEXT) == 0) {
		secptr = (struct section *)((uintptr_t)ptr + sizeof(struct segment_command));
		for (register uint32_t idx = 0; idx < segment.nsects; ++idx) {
			if (__readable(f, &(secptr[idx]), struct section) == TRUE) {
				memcpy(&section, &(secptr[idx]), sizeof(struct section));
				if (m->magic == MH_CIGAM)
					swap_section(&section, 1, NXHostByteOrder());
				if (strcmp(section.sectname, SECT_TEXT) == 0) {
					print_text_section(f, (struct section_64 *)(&section));
					return (EXIT_SUCCESS);
				}
			} else { return (-EXIT_FAILURE); }
		}
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
		if (loadcmd.cmd == LC_SEGMENT)
			if (parse_segment(f, mach, ptr) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				get_section_i386(struct file *f, struct machobj *mach)
{
	struct mach_header	header;
	void			*ptr;

	if (__readable(f, mach->offset, struct mach_header) == TRUE) {
		memcpy(&header, mach->offset, sizeof(struct mach_header));
		if (mach->magic == MH_CIGAM)
			swap_mach_header(&header, NXHostByteOrder());
		ptr = (void *)((uintptr_t)mach->offset + sizeof(struct mach_header));
		for (register uint32_t index = 0; index < header.ncmds; ++index) {
			if (__readable(f, ptr, struct load_command) && ((struct load_command *)ptr)->cmdsize > 0) {
				if (parse_load_command(f, mach, ptr) != EXIT_SUCCESS)
					return (-EXIT_FAILURE);
				ptr = (void *)((uintptr_t)ptr + ((struct load_command *)ptr)->cmdsize);
			} else { return (-EXIT_FAILURE); }
		}
	}
	return (EXIT_SUCCESS);
}
