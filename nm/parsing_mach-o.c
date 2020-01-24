/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mach-o.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:31:26 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/24 13:38:42 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/libsimd.h"
#include "../include/nm.h"
#include "../include/nm_parsing_mach_o.h"
#include "../include/errors.h"

static inline char		*ft_set_name(struct s_mach_section *mach)
{
	return ((char *)(uintptr_t)mach->strtab + mach->symarray[mach->arrsize].entry->n_un.n_strx);
}

static inline size_t		ft_header_size(uint32_t mg)
{
	if (mg == MH_MAGIC || mg == MH_CIGAM)
		return (sizeof(struct mach_header));
	return (sizeof(struct mach_header_64));
}

static void			ft_ld_symtab64_entries(	struct symtab_command *sycom,
							struct s_mach_section *mach)
{
	void const		*symtab = (void *)((uintptr_t)mach->offset + sycom->symoff);

	if (!(mach->symarray = (struct s_symbol *)malloc(sizeof(struct s_symbol) * sycom->nsyms)))
		HANDLE_GNU_ERROR(-EXIT_FAILURE);
	for (unsigned int idx = 0; idx < sycom->nsyms; ++idx) {
		if (!(((struct nlist_64 *)symtab + idx)->n_type & N_STAB)) {
			mach->symarray[mach->arrsize].entry = (struct nlist_64 *)symtab + idx;
			mach->symarray[mach->arrsize].name = ft_set_name(mach);
			++mach->arrsize;
		}
	}
}

static inline int		ft_correct_command(	struct load_command *ptr,
							struct s_file *file)
{
	if (__unlikely(ptr->cmdsize == 0))
		return (EXIT_FALSE);
	if ((uintptr_t)ptr + ptr->cmdsize - (uintptr_t)file->content > file->length)
		return (EXIT_FALSE);
	if ((ptr->cmd == LC_ENCRYPTION_INFO || ptr->cmd == LC_ENCRYPTION_INFO_64)
		&& ((struct encryption_info_command *)ptr)->cryptid != 0)
		return (EXIT_FALSE);
	return (EXIT_TRUE);
}

int				ft_parse_mach_o_file(	struct s_mach_section *mach,
							__pure struct s_file *file)
{
	struct mach_header	header;
	struct load_command	*ldptr;

	ft_memcpy(&header, (void *)mach->offset, sizeof(struct mach_header));
	if (header.magic == MH_CIGAM || header.magic == MH_CIGAM_64)
		swap_mach_header(&header, NXHostByteOrder());
	ldptr = (struct load_command *)((uintptr_t)mach->offset + ft_header_size(header.magic));
	for (unsigned int index = 0; index < header.ncmds; ++index) {
		if (ft_correct_command(ldptr, file) == EXIT_FALSE) {
			FREE_ON_ERROR(mach->arrsize, mach->symarray);
			return (-EXIT_FAILURE);
		}
		if (ldptr->cmd == LC_SYMTAB) {
			mach->strtab = (void *)((uintptr_t)mach->offset + ((struct symtab_command *)ldptr)->stroff);
			ft_ld_symtab64_entries((struct symtab_command *)ldptr, mach);
		}
		else if (ldptr->cmd == LC_SEGMENT || ldptr->cmd == LC_SEGMENT_64)
			ft_parse_segment(mach, (struct segment_command *)ldptr);
		ldptr = (struct load_command *)((uintptr_t)ldptr + ldptr->cmdsize);
	}
	return (EXIT_SUCCESS);
}
