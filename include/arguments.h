/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/17 15:03:41 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ARGUMENTS_H__
# define __ARGUMENTS_H__

# include <unistd.h>

# define OPTION_R	0x00001ul
# define OPTION_U	0x00002ul
# define OPTION_D	0x00004ul
# define OPTION_J	0x00008ul
# define OPTION_P	0x00010ul
# define OPTION_N	0x00020ul

enum			e_needargs {
	no_argument,
	required_argument
};

struct			option {
	char		*fullname;
	size_t		flag;
	int		has_arg;
	int		shortname;
};

struct			arguments {
	char		**arguments;
	size_t		options;
	size_t		size;
};

void			parse_arguments(struct arguments *, int, char const **);

#endif /* __ARGUMENTS_H__ */
