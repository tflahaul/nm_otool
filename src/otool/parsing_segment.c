/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:30:12 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/29 14:48:53 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/nm.h"
#include "../include/errors.h"
#include "../include/nm_parsing_sections.h"

static void			ft_dump_section_64(	struct s_mach_section *mach,
							struct section_64 *ptr)
{
	unsigned char const	*data = (unsigned char const *)((uintptr_t)mach->offset + ptr->offset);

	for (unsigned int index = 0; index < ptr->size; ++index)
		printf("%02x%s", data[index], (index && !(index % 15) ? "\n" : " "));
}

static void			ft_dump_section_32(	struct s_mach_section *mach,
							struct section *ptr)
{
	unsigned char const	*data = (unsigned char const *)((uintptr_t)mach->offset + ptr->offset);

	for (unsigned int index = 0; index < ptr->size; ++index)
		printf("%02x%s", data[index], (index && !(index % 15) ? "\n" : " "));
}

static struct section_64	*ft_data_offset_64(	struct segment_command_64 *cmd,
							struct segment_command_64 *offset,
							struct s_mach_section *mach)
{
	struct section_64	section;
	void			*ptr = (void *)((uintptr_t)offset + sizeof(struct segment_command_64));

	for (unsigned int index = 0; index < cmd->nsects; ++index) {
		memcpy(&section, ptr, sizeof(struct section_64));
		if (mach->magic == MH_CIGAM_64)
			swap_section_64(&section, cmd->nsects, NXHostByteOrder());
		if (strcmp(section.sectname, SECT_TEXT) == EXIT_SUCCESS)
			return ((struct section_64 *)ptr);
		ptr = (struct section_64 *)((uintptr_t)ptr + sizeof(struct section_64));
	}
	return (NULL);
}

static struct section		*ft_data_offset(struct segment_command *cmd,
						struct segment_command *offset,
						struct s_mach_section *mach)
{
	struct section		section;
	void			*ptr = (void *)((uintptr_t)offset + sizeof(struct segment_command));

	for (unsigned int index = 0; index < cmd->nsects; ++index) {
		memcpy(&section, ptr, sizeof(struct section));
		if (mach->magic == MH_CIGAM)
			swap_section(&section, cmd->nsects, NXHostByteOrder());
		if (strcmp(section.sectname, SECT_TEXT) == EXIT_SUCCESS)
			return ((struct section *)ptr);
		ptr = (struct section *)((uintptr_t)ptr + sizeof(struct section));
	}
	return (NULL);
}

int				ft_parse_segment(	struct s_mach_section *mach,
							void *ptr)
{
	struct segment_command		segment32;
	struct segment_command_64	segment64;

	if (((struct load_command *)ptr)->cmd == LC_SEGMENT_64) {
		memcpy(&segment64, ptr, sizeof(struct segment_command_64));
		if (mach->magic == MH_CIGAM_64)
			swap_segment_command_64(&segment64, NXHostByteOrder());
		if (strcmp(segment64.segname, SEG_TEXT) == EXIT_SUCCESS)
			ft_dump_section_64(mach, ft_data_offset_64(&segment64, ptr, mach));
		else
			return (EXIT_FAILURE);
	}
	else
	{
		memcpy(&segment32, ptr, sizeof(struct segment_command));
		if (mach->magic == MH_CIGAM)
			swap_segment_command(&segment32, NXHostByteOrder());
		if (strcmp(segment32.segname, SEG_TEXT) == EXIT_SUCCESS)
			ft_dump_section_32(mach, ft_data_offset(&segment32, ptr, mach));
		else
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
