/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/08 23:28:35 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ARGUMENTS_H__
# define __ARGUMENTS_H__

# include <unistd.h>

# define OPTION_R	0x0000001
# define OPTION_U	0x0000002
# define OPTION_CAPU	0x0000004
# define OPTION_J	0x0000008
# define OPTION_P	0x0000010
# define OPTION_N	0x0000020

enum			e_needargs {
	no_argument,
	required_argument
};

struct			s_option {
	char		*fullname;
	size_t		flag;
	int		has_arg;
	int		shortname;
};

struct			s_arguments {
	char		**arguments;
	size_t		options;
	size_t		size;
};

void			parse_arguments(struct s_arguments *, int, char const **);

#endif /* __ARGUMENTS_H__ */
