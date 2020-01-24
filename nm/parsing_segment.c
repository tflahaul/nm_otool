/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_segment.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 12:30:12 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/24 15:47:26 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/nm.h"
#include "../include/errors.h"
#include "../include/nm_parsing_sections.h"

static struct s_section			*ft_allocate_new_section(void *ptr, int arch)
{
	struct s_section		*node;

	if (!(node = (struct s_section *)malloc(sizeof(struct s_section))))
		return (NULL);
	node->architecture = arch;
	node->offset = ptr;
	node->next = NULL;
	return (node);
}

void					ft_parse_segment(struct s_mach_section *mach,
							 void *ptr)
{
	struct segment_command		*seg32;
	struct segment_command_64	*seg64;
	struct section			*section;
	struct section_64		*section64;

	if (((struct load_command *)ptr)->cmd == LC_SEGMENT_64) {
		seg64 = (struct segment_command_64 *)ptr;
		section64 = (struct section_64 *)((uintptr_t)ptr + sizeof(struct segment_command_64));
		for (unsigned int index = 0; index < seg64->nsects; ++index) {
			ft_push_sect(&(mach->sectlist), ft_allocate_new_section(section64, LC_SEGMENT_64));
			++section64;
		}
	}
	else
	{
		seg32 = (struct segment_command *)ptr;
		section = (struct section *)((uintptr_t)ptr + sizeof(struct segment_command));
		for (unsigned int index = 0; index < seg32->nsects; ++index) {
			ft_push_sect(&(mach->sectlist), ft_allocate_new_section(section, LC_SEGMENT));
			++section;
		}
	}
}
