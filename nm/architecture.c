/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:38 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/24 14:14:29 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "../include/nm.h"
#include "../include/nm_parsing_sections.h"
#include "../include/nm_parsing_mach_o.h"
#include "../include/errors.h"

int				ft_load_file_content(	struct s_file *file,
							char const *prog_name)
{
	int			fd;
	struct stat		informations;

	if ((fd = open(prog_name, O_RDONLY)) < 0)
		return (-EXIT_FAILURE);
	HANDLE_GNU_ERROR(fstat(fd, &informations));
	file->length = informations.st_size;
	file->content = mmap(NULL, file->length, PROT_READ, MAP_PRIVATE, fd, 0);
	if (file->content == MAP_FAILED) {
		HANDLE_GNU_ERROR(close(fd));
		return (-EXIT_FAILURE);
	}
	HANDLE_GNU_ERROR(close(fd));
	return (EXIT_SUCCESS);
}

void				ft_parse_mach_section(	struct s_file *file,
							void *ptr	)
{
	struct s_mach_section	mach;

	memset(&mach, 0, sizeof(struct s_mach_section));
	mach.offset = ptr;
	if (ft_parse_mach_o_file(&mach, file) != EXIT_SUCCESS) {
		HANDLE_GNU_ERROR(munmap(file->content, file->length));
		HANDLE_GNU_ERROR(-EXIT_FAILURE);
	}
	ft_bubble_sort_symbols(&mach, file);
	ft_display_symbols(&mach, file);
	free((void *)mach.symarray);
	ft_free_list(mach.sectlist);
}

int				ft_parse_architecture(	struct s_file *file)
{
	uint32_t const		mc = ((uint32_t *)file->content)[0];

	if (mc == MH_CIGAM || mc == MH_CIGAM_64 || mc == MH_MAGIC || mc == MH_MAGIC_64)
		ft_parse_mach_section(file, (void *)file->content);
	else if (mc == FAT_CIGAM || mc == FAT_CIGAM_64 || mc == FAT_MAGIC || mc == FAT_MAGIC_64)
		ft_handle_FAT_architecture(file);
	else {
		fprintf(stderr, "Unsupported file architecture\n");
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
