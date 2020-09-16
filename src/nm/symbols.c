/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:06:19 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/16 20:28:02 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/errors.h"
#include "../../include/memory.h"
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/swap.h>
#include <string.h>

/*
**	i386 version to get symbols from mach-o section
*/
int				get_symbols_i386(struct s_file_infos *f, struct s_macho_file *mach)
{
	struct mach_header	header;
	struct symtab_command	symtab;
	struct load_command	loadcmd;
	void			*ptr;

	if (__readable(f, mach->offset, struct mach_header) == TRUE) {
		memcpy(&header, mach->offset, sizeof(struct mach_header));
		if (mach->magic == MH_CIGAM)
			swap_mach_header(&header, NXHostByteOrder());
		ptr = (void *)((uintptr_t)mach->offset + sizeof(struct mach_header));
		for (unsigned int index = 0; index < header.ncmds; ++index) {
			if (__readable(f, ptr, struct load_command) == TRUE) {
				memcpy(&loadcmd, ptr, sizeof(struct load_command));
				if (mach->magic == MH_CIGAM)
					swap_load_command(&loadcmd, NXHostByteOrder());
				if ((uintptr_t)ptr + loadcmd.cmdsize <= (uintptr_t)f->head + f->length) {
					if (loadcmd.cmd == LC_SYMTAB) {
						memcpy(&symtab, ptr, sizeof(struct symtab_command));
						mach->strtab = (void *)((uintptr_t)mach->offset + symtab.stroff);
					//	parse_symtab_entries(mach, &symtab); // TODO
					} else if (loadcmd.cmd == LC_SEGMENT) {
					//	parse_segment(mach, (struct segment_command *)ptr); // TODO
					}
				}
				ptr = (void *)((uintptr_t)ptr + loadcmd.cmdsize);
			}
		}
	}
	return (EXIT_SUCCESS);
}

/*
**	x86-64 version to get symbols from mach-o section
*/
int				get_symbols_x86_64(struct s_file_infos *f, struct s_macho_file *mach)
{
	struct mach_header_64	header;
	struct symtab_command	symtab;
	struct load_command	loadcmd;
	void			*ptr;

	if (__readable(f, mach->offset, struct mach_header_64) == TRUE) {
		memcpy(&header, mach->offset, sizeof(struct mach_header_64));
		if (mach->magic == MH_CIGAM_64)
			swap_mach_header_64(&header, NXHostByteOrder());
		ptr = (void *)((uintptr_t)mach->offset + sizeof(struct mach_header_64));
		for (unsigned int index = 0; index < header.ncmds; ++index) {
			if (__readable(f, ptr, struct load_command) == TRUE) {
				memcpy(&loadcmd, ptr, sizeof(struct load_command));
				if (mach->magic == MH_CIGAM_64)
					swap_load_command(&loadcmd, NXHostByteOrder());
				if ((uintptr_t)ptr + loadcmd.cmdsize <= (uintptr_t)f->head + f->length) {
					if (loadcmd.cmd == LC_SYMTAB) {
						memcpy(&symtab, ptr, sizeof(struct symtab_command));
						mach->strtab = (void *)((uintptr_t)mach->offset + symtab.stroff);
					//	parse_symtab_entries(mach, &symtab); // TODO
					} else if (loadcmd.cmd == LC_SEGMENT_64) {
					//	parse_segment(mach, (struct segment_command_64 *)ptr); // TODO
					}
				}
				ptr = (void *)((uintptr_t)ptr + loadcmd.cmdsize);
			}
		}
	}
	return (EXIT_SUCCESS);
}
