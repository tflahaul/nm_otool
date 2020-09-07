/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_into_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/23 12:43:43 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arguments.h"
#include "../../include/errors.h"
#include "../../include/nm.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>

int			map_into_memory(struct s_file_infos *f, char const *fname)
{
	int		fd;
	struct stat	informations;

	HANDLE_NEG_ERROR((fd = open(fname, O_RDONLY)));
	HANDLE_GNU_ERROR(fstat(fd, &informations));
	f->length = (uintptr_t)informations.st_size;
	if ((f->head = mmap(NULL, f->length, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED) {
		HANDLE_GNU_ERROR(close(fd));
		return (-EXIT_FAILURE);
	}
	HANDLE_GNU_ERROR(close(fd));
	return (EXIT_SUCCESS);
}
