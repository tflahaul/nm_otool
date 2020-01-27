/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:31 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/27 12:55:09 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/mman.h>

#include "../include/nm.h"
#include "../include/errors.h"
#include "../include/nm_parsing_mach_o.h"
#include "../include/nm_parsing_options.h"

int				main(int argc, char const **argv)
{
	struct s_file		file;

	memset(&file, 0, sizeof(struct s_file));
	HANDLE_GNU_ERROR(ft_parse_options(&file, argc, argv));
	while (file.filename != NULL && *(file.filename) != NULL) {
		HANDLE_GNU_ERROR(ft_load_file_content(&file, *(file.filename++)));
		HANDLE_GNU_ERROR(ft_parse_architecture(&file));
		HANDLE_GNU_ERROR(munmap((void *)file.content, file.length));
	}
	return (EXIT_SUCCESS);
}
