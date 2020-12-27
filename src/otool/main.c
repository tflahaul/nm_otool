/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:30:56 by thflahau          #+#    #+#             */
/*   Updated: 2020/12/27 13:05:52 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arguments.h"
#include "../../include/errors.h"
#include "../../include/otool.h"
#include "../../include/file.h"
#include <sys/mman.h>
#include <string.h>

int				main(int const argc, char const **argv)
{
	struct file		file;
	struct arguments	args;

	parse_arguments(&args, argc, argv);
	for (args.idx = 0; args.idx < args.size; ++args.idx) {
		if (load_file_informations(&file, args.arguments[args.idx]) == EXIT_SUCCESS) {
			print_section(&file, &args);
			HANDLE_GNU_ERROR(munmap(file.head, file.length), strerror(errno));
		}
	}
	return (EXIT_SUCCESS);
}
