/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/25 10:18:20 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/arguments.h"
#include "../../include/errors.h"
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

static struct option	g_options[] = {
	{"-undefined-only", OPTION_U, no_argument, 'u'},
	{"-defined-only",   OPTION_D, no_argument, 'd'},
	{"-names-only",     OPTION_J, no_argument, 'j'},
	{"-help",           0,        no_argument, 'h'},
	{0, 0, 0, 0}
};

static void		usage(int const stream, char const *file)
{
	int		fd, bytes;
	char		buffer[BUFSIZ];

	HANDLE_NEG_ERROR((fd = open(file, O_RDONLY)), strerror(errno))
	while ((bytes = read(fd, &buffer, BUFSIZ)) > 0)
		write(stream, &buffer, bytes);
	HANDLE_GNU_ERROR(close(fd), strerror(errno));
	exit(EXIT_FAILURE);
}

static struct option	*search_option(char const *arg)
{
	for (unsigned int index = 0; g_options[index].shortname != 0; ++index)
		if (strcmp(arg, g_options[index].fullname) == 0 || arg[0] == g_options[index].shortname)
			return (&(g_options[index]));
	return (NULL);
}

/*
**	'parse_arguments' follows the POSIX command-line arguments convention:
**	"Options precede other non-option arguments". This means you can't intermix
**	options and non-option arguments
*/
void			parse_arguments(struct arguments *args, int ac, char const **av)
{
	unsigned int	index = 0;
	struct option	*option = NULL;

	memset(args, 0, sizeof(struct arguments));
	while (++index < (unsigned int)ac && av[index][0] == '-') {
		if ((option = search_option(av[index] + 1)) == NULL) {
			fprintf(stderr, "ft_nm: invalid option '%s'\n", av[index]);
			usage(STDERR_FILENO, "nm.usage");
		} else if (option->shortname == 'h') {
			usage(STDOUT_FILENO, "nm.usage");
		} else
			args->options |= option->flag;
	}
	args->arguments = (char **)(av + index);
	args->size = (size_t)(ac - index);
}
