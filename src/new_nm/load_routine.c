/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/10 14:55:35 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arguments.h"
#include "../../include/errors.h"
#include "../../include/nm.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>

static inline void	*map_into_memory(int const fd, size_t const length)
{
	void const	*ptr = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);

	if (__builtin_expect((ptr == MAP_FAILED), 0)) {
		HANDLE_GNU_ERROR(close(fd), strerror(errno));
		return (NULL);
	}
	return ((void *)ptr);
}

int			load_file_informations(struct s_file_infos *f, char const *fname)
{
	int		fd;
	struct stat	informations;

	if ((fd = open(fname, O_RDONLY)) < 0)
		return (-fprintf(stderr, "ft_nm: '%s' -> %s\n", fname, strerror(errno)));
	HANDLE_GNU_ERROR(fstat(fd, &informations), strerror(errno));
	f->length = (uintptr_t)informations.st_size;
	if ((f->head = map_into_memory(fd, f->length)) == NULL)
		return (-fprintf(stderr, "ft_nm: '%s' -> %s\n", fname, strerror(errno)));
	HANDLE_GNU_ERROR(close(fd), strerror(errno));
	return (EXIT_SUCCESS);
}
