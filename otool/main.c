/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:14:02 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/23 12:26:07 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "../include/nm.h"
#include "../include/errors.h"

struct				s_content
{
	unsigned char		*content;
	size_t			length;
};

static int			ft_load_file_content(	struct s_content *ptr,
							char const *prog_name)
{
	int			fd;
	struct stat		informations;

	if ((fd = open(prog_name, O_RDONLY)) < 0)
		return (-EXIT_FAILURE);
	HANDLE_GNU_ERROR(fstat(fd, &informations));
	ptr->length = informations.st_size;
	ptr->content = mmap(NULL, ptr->length, PROT_READ, MAP_PRIVATE, fd, 0);
	if (ptr->content == MAP_FAILED) {
		HANDLE_GNU_ERROR(close(fd));
		return (-EXIT_FAILURE);
	}
	HANDLE_GNU_ERROR(close(fd));
	return (EXIT_SUCCESS);
}

int				main(int argc, char const **argv)
{
	struct s_content	file;

	HANDLE_GNU_ERROR(ft_load_file_content(&file, argv[1]));
	HANDLE_GNU_ERROR(munmap(file.content, file.length));
	return (EXIT_SUCCESS);
}
