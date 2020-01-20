/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 09:19:28 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 16:18:07 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/nm.h"
#include "../include/errors.h"
#include "../include/nm_parsing_options.h"

static struct s_options		g_options[] = {
	{"reverse-sort",    OPTION_R,    no_argument, 'r'},
	{"undefined-only",  OPTION_U,    no_argument, 'u'},
	{"defined-only",    OPTION_CAPU, no_argument, 'U'},
	{"names-only",      OPTION_J,    no_argument, 'j'},
	{"no-sort",         OPTION_P,    no_argument, 'p'},
	{"numeric-sort",    OPTION_N,    no_argument, 'n'},
	{0, 0, 0, 0}
};

static inline char		*ft_option_trim(char const *argument)
{
	register unsigned int	index = 0;
	char			*ptr = (char *)argument;

	while (*ptr == '-' && ++index <= 2)
		++ptr;
	return (ptr);
}

static int			ft_long_option_lookup(	struct s_file *file,
							char const *argument)
{
	register unsigned int	index = 0;

	while (g_options[index++].longname != 0) {
		if (strcmp(argument, g_options[index - 1].longname) == 0) {
			file->flags |= g_options[index - 1].flag;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

static int			ft_short_option_lookup(	struct s_file *file,
							char const *argument)
{
	int			ret = EXIT_FAILURE;
	register unsigned int	idx = 0;
	register unsigned int	index = 0;

	while (argument[idx] != 0) {
		while (g_options[index++].longname != 0) {
			if (argument[idx] == g_options[index - 1].shortname) {
				file->flags |= g_options[index - 1].flag;
				ret = EXIT_SUCCESS;
			}
		}
		++idx;
	}
	return (ret);
}

int				ft_parse_options(struct s_file *file, int argc,
						char const **argv)
{
	int		index = 1;

	while (index < argc && argv[index][0] == '-') {
		if (argv[index][1] == '-') {
			HANDLE_GNU_ERROR(ft_long_option_lookup(file, ft_option_trim(argv[index])));
		}
		else if (ft_short_option_lookup(file, ft_option_trim(argv[index])) != EXIT_SUCCESS)
			HANDLE_GNU_ERROR(-EXIT_FAILURE);
		++index;
	}
	file->filename = (char *)argv[index];
	return (EXIT_SUCCESS);
}
