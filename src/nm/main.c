/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:31 by thflahau          #+#    #+#             */
/*   Updated: 2020/11/26 15:12:18 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arguments.h"
#include "../../include/errors.h"
#include "../../include/file.h"
#include "../../include/nm.h"
#include <sys/mman.h>
#include <string.h>

int				main(int const argc, char const **argv)
{
	struct file		file;
	struct arguments	args;

	parse_arguments(&args, argc, argv);
	for (args.idx = 0; args.idx < args.size; ++args.idx) {
		if (load_file_informations(&file, args.arguments[args.idx]) == EXIT_SUCCESS) {
			list_symbols_from_file(&file, &args);
			HANDLE_GNU_ERROR(munmap(file.head, file.length), strerror(errno));
		}
	}
	return (EXIT_SUCCESS);
}
