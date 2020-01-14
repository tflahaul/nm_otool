/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:38 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:35:20 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "include/libsimd.h"
#include "include/nm.h"
#include "include/nm_symlist.h"
#include "include/nm_errors.h"

#define HEADER_SZ(x)	((x) ? sizeof(struct mach_header_64) : sizeof(struct mach_header))

int			ft_load_file_content(	struct s_file *file,
						char const *name	)
{
	int		fd;
	struct stat	informations;

	if ((fd = open(name, O_RDONLY)) < 0)
		return (-EXIT_FAILURE);
	HANDLE_GNU_ERROR(fstat(fd, &informations));
	file->length = informations.st_size;
	file->content = mmap(NULL, file->length, PROT_READ, MAP_PRIVATE, fd, 0);
	if (__unlikely(file->content == MAP_FAILED)) {
		HANDLE_GNU_ERROR(close(fd));
		return (-EXIT_FAILURE);
	}
	HANDLE_GNU_ERROR(close(fd));
	return (EXIT_SUCCESS);
}

static void		ft_ld_symtab64_entries(	struct s_symlist *head,
						__pure struct symtab_command *sycom,
						__pure struct s_file *file)
{
	void const	*symtab = (void *)((uintptr_t)file->content + sycom->symoff);

	for (unsigned int idx = 0; idx < sycom->nsyms; ++idx) {
		if (!(((struct nlist_64 *)symtab + idx)->n_type & N_STAB))
			HANDLE_GNU_ERROR(ft_symlist_push(head, (struct nlist_64 *)symtab + idx));
	}
}

int			ft_parse_mach_o_file(	struct s_symlist *lst,
						struct s_file *file	)
{
	struct mach_header const	*header = (void *)file->content;
	struct load_command		*ldptr;

	file->cpu = !(header->magic == MH_MAGIC || header->magic == MH_CIGAM);
	ldptr = (struct load_command *)(file->content + HEADER_SZ(file->cpu));
	for (unsigned int idx = 0; idx < header->ncmds && ldptr->cmd != LC_SYMTAB; ++idx) {
		if (ldptr->cmdsize == 0) {
			HANDLE_GNU_ERROR(munmap((void *)file->content, file->length));
			return (-EXIT_FAILURE);
		}
		if ((uintptr_t)ldptr + ldptr->cmdsize - (uintptr_t)file->content > file->length) {
			HANDLE_GNU_ERROR(munmap((void *)file->content, file->length));
			return (-EXIT_FAILURE);
		}
		ldptr = (struct load_command *)((uintptr_t)ldptr + ldptr->cmdsize);
	}
	file->strtab = (void *)(file->content + ((struct symtab_command *)ldptr)->stroff);
	ft_ld_symtab64_entries(lst, (struct symtab_command *)ldptr, file);
	return (EXIT_SUCCESS);
}
