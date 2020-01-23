/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:38 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/21 13:35:31 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "../include/nm.h"
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

int				ft_parse_architecture(	struct s_file *file)
{
	uint32_t const		mc = ((uint32_t *)file->content)[0];

	if (mc == MH_CIGAM || mc == MH_CIGAM_64 || mc == MH_MAGIC || mc == MH_MAGIC_64)
		ft_parse_mach_o_file(file, (void *)file->content);
	else if (mc == FAT_CIGAM || mc == FAT_CIGAM_64 || mc == FAT_MAGIC || mc == FAT_MAGIC_64)
		ft_parse_fat(file);
	else {
		fprintf(stderr, "Unsupported file architecture\n");
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
