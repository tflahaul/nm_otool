/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_FAT.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:31:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/23 12:44:29 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/nm.h"
#include "../include/errors.h"
#include "../include/nm_parsing_mach_o.h"

static inline void			ft_initialize_file(struct s_file *file)
{
	file->arrsize = 0;
	file->strtab = NULL;
	file->symarray = NULL;
}

int				ft_parse_fat(struct s_file *file)
{
	char			*offset;
	struct fat_header	header;
	struct fat_arch		architecture;

	memcpy(&header, (void *)file->content, sizeof(struct fat_header));
	if (header.magic == FAT_CIGAM || header.magic == FAT_CIGAM_64) {
		swap_fat_header(&header, NXHostByteOrder());
	}
	offset = (char *)(uintptr_t)file->content + sizeof(struct fat_header);
	for (unsigned int index = 0; index < header.nfat_arch; ++index) {
		ft_initialize_file(file);
		memcpy(&architecture, offset, sizeof(struct fat_arch));
		if (header.magic == FAT_CIGAM || header.magic == FAT_CIGAM_64)
			swap_fat_arch(&architecture, header.nfat_arch - index, NXHostByteOrder());
		ft_parse_mach_o_file(file, offset);
		ft_bubble_sort_symbols(file);
		ft_display_symbols(file);
		offset = offset + architecture.offset;
		free((void *)file->symarray);
	}
	return (EXIT_SUCCESS);
}
