/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:33:18 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/25 17:12:47 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/bytes.h"
#include "../../include/otool.h"
#include "../../include/errors.h"
#include "../../include/arguments.h"
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

static inline int		get_text_section(struct machobj *mach)
{
	return (__is_64_bytes(mach->magic) ? get_section_x86_64(mach) : get_section_i386(mach));
}

static int			get_supported_macho_section(struct machobj *mach)
{
	struct fat_header	header;
	struct fat_arch		archi;
	struct fat_arch		*ptr = (struct fat_arch *)((uintptr_t)mach->object.head + sizeof(struct fat_header));

	if (mach->object.length >= sizeof(struct fat_header)) {
		memcpy(&header, mach->object.head, sizeof(struct fat_header));
		if (header.magic == FAT_CIGAM)
			swap_fat_header(&header, NXHostByteOrder());
		for (register uint32_t index = 0; index < header.nfat_arch; ++index) {
			if (__readable(&(mach->object), &(ptr[index]), struct fat_arch) == TRUE) {
				memcpy(&archi, &(ptr[index]), sizeof(struct fat_arch));
				if (mach->magic == FAT_CIGAM)
					swap_fat_arch(&archi, 1, NXHostByteOrder());
				if (archi.cputype == CPU_TYPE_X86_64 || archi.cputype == CPU_TYPE_I386) {
					mach->object.head = (void *)((uintptr_t)mach->object.head + archi.offset);
					mach->object.length = (size_t)archi.size;
					return (EXIT_SUCCESS);
				}
			} else { return (-EXIT_FAILURE); }
		}
	}
	return (-EXIT_FAILURE);
}

int				print_section(struct file *f, struct arguments *args)
{
	struct machobj		mach;

	memset(&mach, 0, sizeof(struct machobj));
	memcpy(&(mach.object), f, sizeof(struct file));
	mach.magic = safe_read_u32(f, (uintptr_t)f->head);
	if (__is_universal(mach.magic) == TRUE)
		if (get_supported_macho_section(&mach) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
	if (!(mach.magic = safe_read_u32(&(mach.object), (uintptr_t)mach.object.head)))
		return (-fprintf(stderr, "%s: malformed object file\n", args->arguments[args->idx]));
	if (__is_supported(mach.magic) == FALSE)
		return (-fprintf(stderr, "%s: unsupported target\n", args->arguments[args->idx]));
	if (get_text_section(&mach) == EXIT_SUCCESS) {
		// print txt
	} else { fprintf(stderr, "%s: no (__TEXT,__text) section\n", args->arguments[args->idx]); }
	return (EXIT_SUCCESS);
}
