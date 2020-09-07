/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:31 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/29 13:46:01 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arguments.h"
#include "../../include/errors.h"
#include "../../include/nm.h"

int				main(int argc, char const **argv)
{
	struct s_arguments	args;
	struct s_file_infos	file;

	parse_arguments(&args, argc, argv);
	for (unsigned int index = 0; index < args.size; ++index) {
		HANDLE_GNU_ERROR(map_into_memory(&file, args.arguments[index]));
		HANDLE_GNU_ERROR(munmap(file.head, file.length));
	}
	return (EXIT_SUCCESS);
}
