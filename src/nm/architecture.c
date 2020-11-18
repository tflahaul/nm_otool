/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/29 16:28:41 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/bytes.h"
#include "../../include/errors.h"
#include "../../include/sections.h"
#include "../../include/arguments.h"
#if defined __APPLE__
# include <mach-o/loader.h>
# include <mach-o/swap.h>
# include <mach-o/fat.h>
# if defined __i386__
#  define TARGET_CPU_TYPE	CPU_TYPE_I386
# elif defined __x86_64__
#  define TARGET_CPU_TYPE	CPU_TYPE_X86_64
# elif defined __arm__
#  define TARGET_CPU_TYPE	CPU_TYPE_ARM
# elif defined __arm64__
#  define TARGET_CPU_TYPE	CPU_TYPE_ARM64
# else
#  error "CPU architecture is not supported"
# endif
#else
# error "Systems other than macOS are not supported"
#endif /* __APPLE__ */
#include <stdint.h>
#include <unistd.h>
#include <string.h>

static inline int		get_symbols(struct machobj *mach)
{
	return (__is_64_bytes(mach->magic) ? get_symbols_x86_64(mach) : get_symbols_i386(mach));
}

static int			get_supported_macho_section(struct machobj *mach)
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
			if (archi.cputype == TARGET_CPU_TYPE) {
				if ((uintptr_t)mach->object.head + archi.offset + archi.size <= __end_addr(&(mach->object))) {
					mach->object.head = (void *)((uintptr_t)mach->object.head + archi.offset);
					mach->object.length = (size_t)archi.size;
					return (EXIT_SUCCESS);
				} else { return (-EXIT_FAILURE); }
			}
		} else { return (-EXIT_FAILURE); }
	}
	return (-EXIT_FAILURE);
}

int				list_symbols_from_file(struct file *f, struct arguments *args)
{
	struct machobj		mach;

	memset(&mach, 0, sizeof(struct machobj));
	memcpy(&(mach.object), f, sizeof(struct file));
	mach.magic = safe_read_u32(f, f->head);
	if (__is_universal(mach.magic) == TRUE)
		if (get_supported_macho_section(&mach) != EXIT_SUCCESS)
			return (-fprintf(stderr, "%s: malformed fat file\n", args->arguments[args->idx]));
	if (!(mach.magic = safe_read_u32(&(mach.object), mach.object.head)))
		return (-fprintf(stderr, "%s: malformed object file\n", args->arguments[args->idx]));
	if (__is_supported(mach.magic) == FALSE)
		return (-fprintf(stderr, "%s: unsupported target\n", args->arguments[args->idx]));
	if (get_symbols(&mach) == EXIT_SUCCESS) {
		print_symbols(&mach, args);
		free_sections_list(mach.sections_list);
		btree_free(mach.symbols_root);
	} else {
		printf("%s: no symbols\n", args->arguments[args->idx]);
	}
	return (EXIT_SUCCESS);
}
