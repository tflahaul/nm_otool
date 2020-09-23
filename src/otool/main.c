/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:30:56 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/23 18:14:49 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arguments.h"
#include "../../include/errors.h"
#include "../../include/otool.h"
#include "../../include/nm.h"
#include <sys/mman.h>
#include <string.h>

int				main(int argc, char const **argv)
{
	struct file		file;
	struct arguments	args;

	parse_arguments(&args, argc, argv);
	for (unsigned int index = 0; index < args.size; ++index) {
		if (load_file_informations(&file, args.arguments[index]) == EXIT_SUCCESS) {
			print_section(&file, args.options);
			HANDLE_GNU_ERROR(munmap(file.head, file.length), strerror(errno));
		}
	}
	return (EXIT_SUCCESS);
}
