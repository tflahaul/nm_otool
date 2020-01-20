/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:31:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 16:12:38 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/nm.h"

int			ft_parse_fat_file(struct s_file *file)
{
	struct fat_header	header;

	memcpy(&header, (void *)file->content, sizeof(struct fat_header));
	if (header.magic == FAT_CIGAM || header.magic == FAT_CIGAM_64)
		swap_fat_header(&header, NXHostByteOrder());
	for (unsigned int index = 0; index < header.nfat_arch; ++index) {
		printf("Je m'occupe de ça plus tard\n");
	}
	return (EXIT_SUCCESS);
}
