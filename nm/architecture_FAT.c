/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture_FAT.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:31:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/25 15:03:02 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "../include/nm.h"
#include "../include/errors.h"
#include "../include/nm_parsing_mach_o.h"

int				ft_handle_FAT_architecture(struct s_file *file)
{
	uint32_t		magic;
	struct fat_header	header;
	struct fat_arch		architectures;
	struct fat_arch		*offset;

	memcpy(&header, (void *)file->content, sizeof(struct fat_header));
	magic = header.magic;
	if (header.magic == FAT_CIGAM || header.magic == FAT_CIGAM_64)
		swap_fat_header(&header, NXHostByteOrder());
	offset = (struct fat_arch *)((uintptr_t)file->content + sizeof(struct fat_header));
	for (unsigned int index = 0; index < header.nfat_arch; ++index) {
		memcpy(&architectures, offset++, sizeof(struct fat_arch));
		if (magic == FAT_CIGAM || magic == FAT_CIGAM_64)
			swap_fat_arch(&architectures, header.nfat_arch, NXHostByteOrder());
		if (architectures.cputype == CPU_TYPE_X86_64) {
			ft_parse_mach_section(file, (void *)((uintptr_t)file->content + architectures.offset));
			break ;
		}
	}
	return (EXIT_SUCCESS);
}
