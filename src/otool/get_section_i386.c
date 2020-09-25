/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_i386.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:37:20 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/25 17:09:21 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/errors.h"
#include "../../include/bytes.h"
#include "../../include/sections.h"
#include "../../include/otool.h"
#if defined __APPLE__
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/swap.h>
#else
# error "Systems other than macOS are not supported"
#endif /* __APPLE */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int			parse_segment(struct machobj *mach, void const *off)
{
	struct segment_command	segment;
	struct section		section;
	struct section		*secptr;

	memcpy(&segment, off, sizeof(struct segment_command));
	if (mach->magic == MH_CIGAM)
		swap_segment_command(&segment, NXHostByteOrder());
	if (strcmp(segment.segname, SEG_TEXT) == 0) {
		secptr = (struct section *)((uintptr_t)off + sizeof(struct segment_command));
		for (register uint32_t idx = 0; idx < segment.nsects; ++idx) {
			if (__readable(&(mach->object), &(secptr[idx]), struct section) == TRUE) {
				memcpy(&section, &(secptr[idx]), sizeof(struct section));
				if (mach->magic == MH_CIGAM)
					swap_section(&section, 1, NXHostByteOrder());
				if (strcmp(section.sectname, SECT_TEXT) == 0) {
					print_text_section(&(mach->object), (struct section_64 *)(&section));
					return (EXIT_SUCCESS);
				}
			} else { return (-EXIT_FAILURE); }
		}
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
		if (loadcmd.cmd == LC_SEGMENT)
			if (parse_segment(mach, off) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				get_section_i386(struct machobj *mach)
{
	struct mach_header	header;
	struct load_command	*ptr;

	if (__readable(&(mach->object), mach->object.head, struct mach_header)) {
		memcpy(&header, mach->object.head, sizeof(struct mach_header));
		if (mach->magic == MH_CIGAM)
			swap_mach_header(&header, NXHostByteOrder());
		ptr = (struct load_command *)((uintptr_t)mach->object.head + sizeof(struct mach_header));
		for (register uint32_t index = 0; index < header.ncmds; ++index) {
			if (__readable(&(mach->object), ptr, struct load_command) && ptr->cmdsize > 0) {
				if (parse_load_command(mach, ptr) != EXIT_SUCCESS)
					return (-EXIT_FAILURE);
				ptr = (void *)((uintptr_t)ptr + ptr->cmdsize);
			} else { return (-EXIT_FAILURE); }
		}
	}
	return (EXIT_SUCCESS);
}
