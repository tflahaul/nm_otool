/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/09 18:34:25 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/memory.h"
#include "../../include/nm.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static int		get_symbols(struct s_file_infos *f, struct s_macho_file *macho)
{
	return (EXIT_SUCCESS);
}

static int		parse_macho_section(struct s_file_infos *f, uintptr_t off)
{
	struct s_macho_file	macho;

	memset(&macho, 0, sizeof(struct s_macho_file));
	macho.offset = (void *)((uintptr_t)f->head + off);
	macho.magic = safe_read_u32(f, (uintptr_t)macho.offset);
	if (__is_supported(macho.magic) == EXIT_FALSE)
		return (-fprintf(stderr, "ft_nm: Unsupported target\n"));
	if (get_symbols(f, &macho) == EXIT_SUCCESS) {
		// sort symbols
		// display symbols
		// free symbols
	}
	return (EXIT_SUCCESS);
}

int			architecture_dispatch(struct s_file_infos *f)
{
	uintptr_t	offset = 0;
	uint32_t const	magic = safe_read_u32(f, (uintptr_t)f->head);

//	if (magic == FAT_CIGAM || magic == FAT_MAGIC || magic == FAT_CIGAM_64 || magic == FAT_MAGIC_64)
//		get supported macho offset from FAT
	parse_macho_section(f, offset);
	return (EXIT_SUCCESS);
}
