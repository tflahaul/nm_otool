/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mach_o.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:38 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 13:33:54 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/libsimd.h"
#include "../include/nm.h"
#include "../include/nm_errors.h"

#define EXIT_FALSE	0
#define EXIT_TRUE	1
#define HEADER_SZ(x)	((x) ? sizeof(struct mach_header_64) : sizeof(struct mach_header))

static inline char	*ft_get_name(struct s_file *file)
{
	return ((char *)(uintptr_t)file->strtab + file->symarray[file->arrsize].entry->n_un.n_strx);
}

int			ft_load_file_content(	struct s_file *file,
						char const *prog_name	)
{
	int		fd;
	struct stat	informations;

	if ((fd = open(prog_name, O_RDONLY)) < 0)
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

static void		ft_ld_symtab64_entries(	__pure struct symtab_command *sycom,
						__pure struct s_file *file)
{
	void const	*symtab = (void *)((uintptr_t)file->content + sycom->symoff);

	if (!(file->symarray = (struct s_symbol *)malloc(sizeof(struct s_symbol) * sycom->nsyms)))
		HANDLE_GNU_ERROR(-EXIT_FAILURE);
	for (unsigned int idx = 0; idx < sycom->nsyms; ++idx) {
		if (!(((struct nlist_64 *)symtab + idx)->n_type & N_STAB)) {
			file->symarray[file->arrsize].entry = (struct nlist_64 *)symtab + idx;
			file->symarray[file->arrsize].name = ft_get_name(file);
			++file->arrsize;
		}
	}
}

static inline int	ft_is_supported_arch(unsigned int magic)
{
	switch (magic)
	{
	case MH_MAGIC_64:
		break ;
	case MH_MAGIC:
		break ;
	case FAT_MAGIC_64:
		break ;
	case FAT_MAGIC:
		break ;
	default:
		return (EXIT_FALSE);
	}
	return (EXIT_TRUE);
}

int			ft_parse_mach_o_file(	struct s_file *file	)
{
	struct mach_header const	*header = (void *)file->content;
	struct load_command		*ldptr;

	if (ft_is_supported_arch(header->magic == EXIT_FALSE))
		return (-EXIT_FAILURE);
	ldptr = (struct load_command *)(file->content + HEADER_SZ(header->magic == MH_MAGIC_64));
	for (unsigned int idx = 0; idx < header->ncmds && ldptr->cmd != LC_SYMTAB; ++idx) {
		if (ldptr->cmdsize == 0) {
			HANDLE_GNU_ERROR(munmap((void *)file->content, file->length));
			return (-EXIT_FAILURE);
		}
		if ((uintptr_t)ldptr + ldptr->cmdsize - (uintptr_t)file->content > file->length) {
			HANDLE_GNU_ERROR(munmap((void *)file->content, file->length));
			return (-EXIT_FAILURE);
		}
		if ((ldptr->cmd == LC_ENCRYPTION_INFO || ldptr->cmd == LC_ENCRYPTION_INFO_64) \
			&& ((struct encryption_info_command *)ldptr)->cryptid) {
			HANDLE_GNU_ERROR(munmap((void *)file->content, file->length));
			return (-EXIT_FAILURE);
		}
		ldptr = (struct load_command *)((uintptr_t)ldptr + ldptr->cmdsize);
	}
	file->strtab = (void *)(file->content + ((struct symtab_command *)ldptr)->stroff);
	ft_ld_symtab64_entries((struct symtab_command *)ldptr, file);
	return (EXIT_SUCCESS);
}
