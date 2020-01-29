/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:31 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/29 14:11:36 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <sys/mman.h>

#include "../include/nm.h"
#include "../include/errors.h"
#include "../include/nm_parsing_mach_o.h"
#include "../include/nm_parsing_options.h"

int				main(__unused int argc, char const **argv)
{
	int			mbin = 0;
	struct s_file		file;

	memset(&file, 0, sizeof(struct s_file));
	if (argv[1] != NULL && argv[2] != NULL)
		mbin = 1;
	while (*(++argv) != NULL) {
		if (mbin != 0)
			printf("\n%s:\n", *argv);
		HANDLE_GNU_ERROR(ft_load_file_content(&file, *argv));
		HANDLE_GNU_ERROR(ft_parse_architecture(&file));
		HANDLE_GNU_ERROR(munmap((void *)file.content, file.length));
	}
	return (EXIT_SUCCESS);
}
