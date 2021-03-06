/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:37:18 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/30 19:15:51 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"
#include "../../include/otool.h"
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

static int			parse_segment(struct machsect *mach, uint32_t nsects, void const *off)
{
	struct section_64	section;
	struct section_64	*secptr;

	secptr = (struct section_64 *)((uintptr_t)off + sizeof(struct segment_command_64));
	for (register uint32_t index = 0; index < nsects; ++index) {
		if (__is_readable(&(mach->object), &(secptr[index]), sizeof(struct section_64))) {
			memcpy(&section, &(secptr[index]), sizeof(struct section_64));
			if (mach->magic == MH_CIGAM_64)
				swap_section_64(&section, 1, NXHostByteOrder());
			if (strcmp(section.segname, SEG_TEXT) == 0 && strcmp(section.sectname, mach->target) == 0) {
				if ((uintptr_t)mach->object.head + section.offset + section.size < __end_addr(&(mach->object))) {
					mach->section.head = (void *)((uintptr_t)mach->object.head + section.offset);
					mach->section.length = (uintptr_t)section.size;
					mach->offset = section.offset;
					break;
				}
			}
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}

static int			parse_load_command(struct machsect *mach, void const *off)
{
	struct load_command		loadcmd;
	struct segment_command_64	segment;

	memcpy(&loadcmd, off, sizeof(struct load_command));
	if (mach->magic == MH_CIGAM_64)
		swap_load_command(&loadcmd, NXHostByteOrder());
	if ((uintptr_t)off + loadcmd.cmdsize <= __end_addr(&(mach->object))) {
		if (loadcmd.cmd == LC_SEGMENT_64) {
			memcpy(&segment, off, sizeof(struct segment_command_64));
			if (mach->magic == MH_CIGAM_64)
				swap_segment_command_64(&segment, NXHostByteOrder());
			if (parse_segment(mach, segment.nsects, off) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
			else if (mach->section.head != NULL)
				return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}

int				get_section_64(struct machsect *mach)
{
	struct mach_header_64	header;
	struct load_command	*ptr;

	if (mach->object.length < sizeof(struct mach_header_64))
		return (-EXIT_FAILURE);
	memcpy(&header, mach->object.head, sizeof(struct mach_header_64));
	if (mach->magic == MH_CIGAM_64)
		swap_mach_header_64(&header, NXHostByteOrder());
	ptr = (struct load_command *)((uintptr_t)mach->object.head + sizeof(struct mach_header_64));
	for (unsigned int index = 0; index < header.ncmds; ++index) {
		if (__is_readable(&(mach->object), ptr, sizeof(struct load_command)) && ptr->cmdsize > 0) {
			if (parse_load_command(mach, ptr) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
			else if (mach->section.head != NULL)
				break;
			ptr = (void *)((uintptr_t)ptr + ptr->cmdsize);
		} else { return (-EXIT_FAILURE); }
	}
	return (EXIT_SUCCESS);
}
