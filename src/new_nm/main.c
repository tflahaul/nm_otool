/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:31 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/08 22:22:37 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arguments.h"
#include "../../include/errors.h"
#include "../../include/nm.h"
#include <sys/mman.h>
#include <string.h>

int				main(int argc, char const **argv)
{
	struct s_arguments	args;
	struct s_file_infos	file;

	parse_arguments(&args, argc, argv);
	for (unsigned int index = 0; index < args.size; ++index) {
		if (load_file_informations(&file, args.arguments[index]) == EXIT_SUCCESS) {
			architecture_dispatch(&file);
			HANDLE_GNU_ERROR(munmap(file.head, file.length), strerror(errno));
		}
	}
	return (EXIT_SUCCESS);
}
