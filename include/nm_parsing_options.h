/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_parsing_options.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 08:40:24 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 13:05:49 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_PARSING_OPTIONS_H__
# define __NM_PARSING_OPTIONS_H__

# include "nm.h"

# define OPTION_R		0x0000001
# define OPTION_U		0x0000002
# define OPTION_CAPU		0x0000004
# define OPTION_J		0x0000008
# define OPTION_P		0x0000010
# define OPTION_N		0x0000020

enum				e_needargs {
	no_argument,
	required_argument
};

struct				s_options {
	char			*longname;
	size_t			flag;
	int			has_arg;
	int			shortname;
};

int				ft_parse_options(struct s_file *, int, char const **);

#endif /* __NM_PARSING_OPTIONS_H__ */
