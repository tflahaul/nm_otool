/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:33:18 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/29 16:27:52 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"
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
#endif /* __APPLE__ */
#include <stdint.h>
#include <unistd.h>
#include <string.h>

static inline int		get_target_section(struct machsect *mach)
{
	return (__is_64_bytes(mach->magic) ? get_section_x86_64(mach) : get_section_i386(mach));
}

static int			get_supported_macho_section(struct machsect *mach)
{
	struct fat_header	header;
	struct fat_arch		archi;
	struct fat_arch		*ptr = (struct fat_arch *)((uintptr_t)mach->object.head + sizeof(struct fat_header));

	if (mach->object.length < sizeof(struct fat_header))
		return (-EXIT_FAILURE);
	memcpy(&header, mach->object.head, sizeof(struct fat_header));
	if (header.magic == FAT_CIGAM)
		swap_fat_header(&header, NXHostByteOrder());
	for (register uint32_t index = 0; index < header.nfat_arch; ++index) {
		if (__is_readable(&(mach->object), &(ptr[index]), sizeof(struct fat_arch))) {
			memcpy(&archi, &(ptr[index]), sizeof(struct fat_arch));
			if (mach->magic == FAT_CIGAM)
				swap_fat_arch(&archi, 1, NXHostByteOrder());
			if (archi.cputype == CPU_TYPE_X86_64 || archi.cputype == CPU_TYPE_I386) {
				if ((uintptr_t)mach->object.head + archi.offset + archi.size < __end_addr(&(mach->object))) {
					mach->object.head = (void *)((uintptr_t)mach->object.head + archi.offset);
					mach->object.length = (size_t)archi.size;
					return (EXIT_SUCCESS);
				} else { return (-EXIT_FAILURE); }
			}
		} else { return (-EXIT_FAILURE); }
	}
	return (-EXIT_FAILURE);
}

int				print_section(struct file *f, struct arguments *args)
{
	struct machsect		mach;

	memset(&mach, 0, sizeof(struct machsect));
	memcpy(&(mach.object), f, sizeof(struct file));
	mach.magic = safe_read_u32(f, f->head);
	mach.target = (args->options & OPTION_S) ? "__cstring" : SECT_TEXT;
	if (__is_universal(mach.magic) == TRUE)
		if (get_supported_macho_section(&mach) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
	if (!(mach.magic = safe_read_u32(&(mach.object), mach.object.head)))
		return (-fprintf(stderr, "%s: malformed object file\n", args->arguments[args->idx]));
	if (__is_supported(mach.magic) == FALSE)
		return (-fprintf(stderr, "%s: unsupported target\n", args->arguments[args->idx]));
	if (get_target_section(&mach) == EXIT_SUCCESS && mach.section.head != NULL && mach.section.length > 0) {
		if (args->options & OPTION_S)
			print_strings_section(&mach, args);
		else
			print_text_section(&mach, args);
	} else {
		fprintf(stderr, "%s: no (__TEXT,%s) section\n", args->arguments[args->idx], mach.target);
	}
	return (EXIT_SUCCESS);
}
