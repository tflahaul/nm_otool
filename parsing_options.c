/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 09:19:28 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:35:36 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/nm.h"
#include "include/nm_errors.h"
#include "include/nm_parsing_options.h"

static t_options	g_options[] = {
	{"reverse", OPTION_R,    no_argument, 'r'},
	{"undef",   OPTION_U,    no_argument, 'u'},
	{"noundef", OPTION_CAPU, no_argument, 'U'},
	{"names",   OPTION_J,    no_argument, 'j'},
	{"nosort",  OPTION_P,    no_argument, 'p'},
	{0, 0, 0, 0}
};

static inline char		*ft_option_trim(char const *argument)
{
	char			*ptr;
	register unsigned int	index;

	index = 0;
	ptr = (char *)argument;
	while (*ptr == '-' && ++index <= 2)
		++ptr;
	return (ptr);
}

static inline int		ft_long_option_lookup(char const *argument)
{
	register unsigned int	index;

	index = 0;
	while (g_options[index++].longname != 0)
		if (strcmp(argument, g_options[index - 1].longname) == 0)
			return (index - 1);
	return (index);
}

static inline int		ft_short_option_lookup(char const *argument)
{
	register unsigned int	index;

	index = 0;
	if (argument[1])
		return (4);
	while (g_options[index++].longname != 0)
		if (argument[0] == g_options[index - 1].shortname)
			return (index - 1);
	return (index);
}

int				ft_parse_options(struct s_file *file, int argc,
							char const **argv)
{
	int		index;
	int		ret = EXIT_SUCCESS;

	index = 1;
	while (index < argc && argv[index][0] == '-') {
		if (argv[index][1] == '-')
			ret = ft_long_option_lookup(ft_option_trim(argv[index]));
		else
			ret = ft_short_option_lookup(ft_option_trim(argv[index]));
		HANDLE_GNU_ERROR(ret);
		file->flags &= g_options[ret].flag;
		++index;
	}
	file->filename = (char *)argv[index];
	return (EXIT_SUCCESS);
}
