/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mach-o.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:31:26 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/29 14:39:58 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/nm.h"
#include "../include/otool_parsing.h"
#include "../include/errors.h"

static inline size_t		ft_header_size(uint32_t mg)
{
	if (mg == MH_MAGIC || mg == MH_CIGAM)
		return (sizeof(struct mach_header));
	return (sizeof(struct mach_header_64));
}

static inline int		ft_parsable_command(	struct load_command *ptr,
							struct s_file *file)
{
	if (ptr->cmdsize == 0)
		return (EXIT_FALSE);
	if ((uintptr_t)ptr + ptr->cmdsize - (uintptr_t)file->content > file->length)
		return (EXIT_FALSE);
	if ((ptr->cmd == LC_ENCRYPTION_INFO || ptr->cmd == LC_ENCRYPTION_INFO_64)
		&& ((struct encryption_info_command *)ptr)->cryptid != 0)
		return (EXIT_FALSE);
	return (EXIT_TRUE);
}

int				ft_parse_mach_o_file(	struct s_mach_section *mach,
							__pure struct s_file *file)
{
	struct mach_header	header;
	struct load_command	*ldptr;

	memcpy(&header, (void *)mach->offset, sizeof(struct mach_header));
	if (header.magic == MH_CIGAM || header.magic == MH_CIGAM_64)
		swap_mach_header(&header, NXHostByteOrder());
	ldptr = (struct load_command *)((uintptr_t)mach->offset + ft_header_size(header.magic));
	for (unsigned int index = 0; index < header.ncmds; ++index) {
		if (ft_parsable_command(ldptr, file) == EXIT_FALSE) {
			FREE_ON_ERROR(mach->arrsize, mach->symarray);
			return (-EXIT_FAILURE);
		}
		if ((ldptr->cmd == LC_SEGMENT) || (ldptr->cmd == LC_SEGMENT_64))
			if (ft_parse_segment(mach, (void *)ldptr) == EXIT_SUCCESS)
				break ;
		ldptr = (struct load_command *)((uintptr_t)ldptr + ldptr->cmdsize);
	}
	return (EXIT_SUCCESS);
}
