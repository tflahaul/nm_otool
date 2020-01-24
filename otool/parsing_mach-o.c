/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mach-o.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 16:04:33 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/24 16:19:16 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "../include/nm.h"
#include "../include/errors.h"

static inline size_t		ft_header_size(uint32_t mg)
{
	if (mg == MH_MAGIC || mg == MH_CIGAM)
		return (sizeof(struct mach_header));
	return (sizeof(struct mach_header_64));
}

static inline int		ft_correct_command(	struct load_command *ptr,
							struct s_file *file)
{
	if (__unlikely(ptr->cmdsize == 0))
		return (EXIT_FALSE);
	if ((uintptr_t)ptr + ptr->cmdsize - (uintptr_t)file->content > file->length)
		return (EXIT_FALSE);
	if ((ptr->cmd == LC_ENCRYPTION_INFO || ptr->cmd == LC_ENCRYPTION_INFO_64)
		&& ((struct encryption_info_command *)ptr)->cryptid != 0)
		return (EXIT_FALSE);
	return (EXIT_TRUE);
}

static void			ft_dump_text_section(	struct s_mach_section *mach,
							size_t offset, size_t size)
{
	void			*ptr = mach->offset + offset;

	for (unsigned int index = 0; index < size; ++index) {
		printf("%#x ", (int)((unsigned char *)ptr)[index]);
		if (!(index % 32))
			printf("\n");
	}
}

// pas tres lisible tout ça
int				foo(struct s_mach_section *mach, struct s_file *file)
{
	struct mach_header	header;
	struct load_command	*ldptr;

	ft_memcpy(&header, (void *)mach->offset, sizeof(struct mach_header));
	if (header.magic == MH_CIGAM || header.magic == MH_CIGAM_64)
		swap_mach_header(&header, NXHostByteOrder());
	ldptr = (struct load_command *)((uintptr_t)mach->offset + ft_header_size(header.magic));
	for (unsigned int index = 0; index < header.ncmds; ++index) {
		if (ft_correct_command(ldptr, file) == EXIT_FALSE) {
			FREE_ON_ERROR(mach->arrsize, mach->symarray);
			return (-EXIT_FAILURE);
		}
		else if (ldptr->cmd == LC_SEGMENT || ldptr->cmd == LC_SEGMENT_64) {
			if ((ldptr->cmd == LC_SEGMENT_64) && !strcmp(((struct segment_command_64 *)ldptr)->segname, SEG_TEXT))
				ft_dump_text_section(mach, ((struct segment_command_64 *)ldptr)->fileoff, \
					((struct segment_command_64 *)ldptr)->filesize);
			else if (!strcmp(((struct segment_command *)ldptr)->segname , SEG_TEXT))
				ft_dump_text_section(mach, ((struct segment_command *)ldptr)->fileoff, \
					((struct segment_command *)ldptr)->filesize);
		}
		ldptr = (struct load_command *)((uintptr_t)ldptr + ldptr->cmdsize);
	}
	return (EXIT_SUCCESS);
}
