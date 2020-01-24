/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture_FAT.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:31:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/24 15:22:09 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

#include "../include/nm.h"
#include "../include/errors.h"
#include "../include/nm_parsing_mach_o.h"

int				ft_handle_FAT_architecture(struct s_file *file)
{
	void			*offset;
	struct fat_header	header;
	struct fat_arch		*architectures;

	memcpy(&header, (void *)file->content, sizeof(struct fat_header));
	if (header.magic == FAT_CIGAM || header.magic == FAT_CIGAM_64) {
		swap_fat_header(&header, NXHostByteOrder());
	}
	offset = (void *)((uintptr_t)file->content + sizeof(struct fat_header));
	if (!(architectures = (struct fat_arch *)malloc(sizeof(struct fat_arch) * header.nfat_arch)))
		return (-EXIT_FAILURE);
	for (unsigned int index = 0; index < header.nfat_arch; ++index) {
		memcpy(&(architectures[index]), offset, sizeof(struct fat_arch));
		if (header.magic == FAT_CIGAM || header.magic == FAT_CIGAM_64)
			swap_fat_arch(&(architectures[index]), header.nfat_arch, NXHostByteOrder());
		offset = (void *)((uintptr_t)offset + sizeof(struct fat_arch));
	}
	for (unsigned int index = 0; index < header.nfat_arch; ++index) {
		ft_parse_mach_section(file, offset);
		offset = (void *)((uintptr_t)offset + architectures[index].size);
	}
	free((void *)architectures);
	return (EXIT_SUCCESS);
}
