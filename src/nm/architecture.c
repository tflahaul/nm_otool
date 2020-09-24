/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/24 10:56:27 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/errors.h"
#include "../../include/bytes.h"
#include "../../include/parsing.h"
#include "../../include/sections.h"
#include "../../include/nm.h"
#if defined __APPLE__
# include <mach-o/loader.h>
# include <mach-o/swap.h>
# include <mach-o/fat.h>
#else
# error "Systems other than macOS are not supported"
#endif /* __APPLE */
#include <stdint.h>
#include <unistd.h>
#include <string.h>

static inline int		get_symbols(struct file *f, struct machobj *m)
{
	return (__is_64_bytes(m->magic) ? get_symbols_x86_64(f, m) : get_symbols_i386(f, m));
}

static ssize_t			get_supported_macho_section(struct file *f)
{
	struct fat_header	header;
	struct fat_arch		architecture;
	struct fat_arch		*ptr = (struct fat_arch *)((uintptr_t)f->head + sizeof(struct fat_header));

	if (f->length >= sizeof(struct fat_header)) {
		memcpy(&header, f->head, sizeof(struct fat_header));
		if (header.magic == FAT_CIGAM) {
			swap_fat_header(&header, NXHostByteOrder());
			header.magic = swap_uint32(header.magic);
		}
		for (register uint32_t index = 0; index < header.nfat_arch; ++index) {
			if (__readable(f, &(ptr[index]), struct fat_arch) == TRUE) {
				memcpy(&architecture, &(ptr[index]), sizeof(struct fat_arch));
				if (header.magic == FAT_CIGAM)
					swap_fat_arch(&architecture, 1, NXHostByteOrder());
				if (architecture.cputype == CPU_TYPE_X86_64 || architecture.cputype == CPU_TYPE_I386)
					return ((ssize_t)architecture.offset);
			} else { return (-EXIT_FAILURE); }
		}
	}
	return (-EXIT_FAILURE);
}

int				list_symbols_from_file(struct file *f, size_t opt)
{
	ssize_t			off = 0;
	uint32_t const		magic = safe_read_u32(f, (uintptr_t)f->head);
	struct machobj		macho;

	memset(&macho, 0, sizeof(struct machobj));
	macho.offset = f->head;
	if (__is_universal(magic) == TRUE)
		if ((off = get_supported_macho_section(f)) > 0)
			macho.offset = (void *)((uintptr_t)f->head + (uintptr_t)off);
	macho.magic = safe_read_u32(f, (uintptr_t)macho.offset);
	if (__is_supported(macho.magic) == FALSE)
		return (-fputs("ft_nm: unsupported target\n", stderr));
	if (get_symbols(f, &macho) == EXIT_SUCCESS) {
//		sort_symbols(f, &macho, opt);
		print_symbols(f, &macho, opt);
		free_sections_list(macho.sections_list);
		free_symbols_list(macho.symbols_list);
	} else { puts("ft_nm: no symbols"); }
	return (EXIT_SUCCESS);
}
