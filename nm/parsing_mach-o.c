/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mach-o.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:31:26 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 16:17:49 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/nm.h"
#include "../include/errors.h"

static inline char	*ft_set_name(struct s_file *file)
{
	return ((char *)(uintptr_t)file->strtab + file->symarray[file->arrsize].entry->n_un.n_strx);
}

static inline size_t	ft_header_size(uint32_t mg)
{
	if (mg == MH_MAGIC || mg == MH_CIGAM)
		return (sizeof(struct mach_header));
	return (sizeof(struct mach_header_64));
}

static void		ft_ld_symtab64_entries(	__pure struct symtab_command *sycom,
						__pure struct s_file *file)
{
	void const	*symtab = (void *)((uintptr_t)file->content + sycom->symoff);

	if (!(file->symarray = (struct s_symbol *)malloc(sizeof(struct s_symbol) * sycom->nsyms)))
		HANDLE_GNU_ERROR(-EXIT_FAILURE);
	for (unsigned int idx = 0; idx < sycom->nsyms; ++idx) {
		if (!(((struct nlist_64 *)symtab + idx)->n_type & N_STAB)) {
			file->symarray[file->arrsize].entry ft_header_size= (struct nlist_64 *)symtab + idx;
			file->symarray[file->arrsize].name = ft_set_name(file);
			++file->arrsize;
		}
	}
}

int			ft_parse_mach_o_file(	__pure struct s_file *file)
{
	struct mach_header_64		header;
	struct load_command		*ldptr;

	memcpy(&header, (void *)file->content, sizeof(struct mach_header_64));
	if (header.magic == MH_CIGAM || header.magic == MH_CIGAM_64)
		swap_mach_header_64(&header, NXHostByteOrder());
	ldptr = (struct load_command *)(file->content + ft_header_size(header.magic));
	for (unsigned int idx = 0; idx < header.ncmds && ldptr->cmd != LC_SYMTAB; ++idx) {
		if (ldptr->cmdsize == 0) {
			HANDLE_GNU_ERROR(munmap((void *)file->content, file->length));
			return (-EXIT_FAILURE);
		}
		if ((uintptr_t)ldptr + ldptr->cmdsize - (uintptr_t)file->content > file->length) {
			HANDLE_GNU_ERROR(munmap((void *)file->content, file->length));
			return (-EXIT_FAILURE);
		}
		if ((ldptr->cmd == LC_ENCRYPTION_INFO || ldptr->cmd == LC_ENCRYPTION_INFO_64) \
			&& ((struct encryption_info_command *)ldptr)->cryptid != 0) {
			HANDLE_GNU_ERROR(munmap((void *)file->content, file->length));
			return (-EXIT_FAILURE);
		}
		ldptr = (struct load_command *)((uintptr_t)ldptr + ldptr->cmdsize);
	}
	file->strtab = (void *)(file->content + ((struct symtab_command *)ldptr)->stroff);
	ft_ld_symtab64_entries((struct symtab_command *)ldptr, file);
	return (EXIT_SUCCESS);
}
