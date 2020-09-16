/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/16 11:25:30 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/memory.h"
#include "../../include/nm.h"
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static int			get_symbols(struct s_file_infos *f, struct s_macho_file *macho)
{
	return (EXIT_FAILURE);
}

static ssize_t			get_supported_macho_section(struct s_file_infos *f)
{
	struct fat_header	header;
	struct fat_arch		architecture;
	struct fat_arch		*ptr = (struct fat_arch *)((uintptr_t)f->head + sizeof(struct fat_header));

	if (f->length >= sizeof(struct fat_header)) {
		memset(&header, f->head, sizeof(struct fat_header));
		if (header.magic == FAT_CIGAM)
			swap_fat_header(&header, NXHostByteOrder());
		for (unsigned int index = 0; index < header.nfat_arch; ++index) {
			if (__readable(f, &(ptr[index]), struct fat_arch) == EXIT_TRUE) {
				memcpy(&architecture, &(ptr[index]), sizeof(struct fat_arch))
				if (header.magic == FAT_CIGAM)
					swap_fat_arch(&architecture, 1, NXHostByteOrder());
				if (architecture.cputype == 0 /* get machine cpu type */)
					return ((ssize_t)ptr.offset);
			}
		}
	}
	return (-EXIT_FAILURE);
}

int				list_symbols_from_file(struct s_file_infos *f, size_t opt)
{
	ssize_t			off = 0;
	uint32_t const		magic = safe_read_u32(f, (uintptr_t)f->head);
	struct s_macho_file	macho;

	memset(&macho, 0, sizeof(struct s_macho_file));
	macho.offset = f->head;
	if (__is_universal(magic) == EXIT_TRUE)
		if ((off = get_supported_macho_section(f)) > 0)
			macho.offset = (void *)((uintptr_t)f->head + (uintptr_t)off);
	macho.magic = safe_read_u32(f, (uintptr_t)macho.offset);
	if (__is_supported(macho.magic) == EXIT_FALSE)
		return (-fputs("ft_nm: unsupported target\n", stderr));
	if (get_symbols(f, &macho) == EXIT_SUCCESS) {
		// sort symbols
		// display symbols
		// free symbols
	} else { puts("ft_nm: no symbols"); }
	return (EXIT_SUCCESS);
}
