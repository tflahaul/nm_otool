/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 16:14:02 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/24 16:19:04 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "../include/nm.h"
#include "../include/nm_parsing_mach_o.h"
#include "../include/errors.h"

int				main(int argc, char const **argv)
{
	struct s_file		file;

	while (*(file.filename) != NULL) {
		HANDLE_GNU_ERROR(ft_load_file_content(&file, *file.filename++));
		HANDLE_GNU_ERROR(munmap(file.content, file.length));
	}
	return (EXIT_SUCCESS);
}
