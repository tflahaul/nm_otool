/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_parsing_options.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 08:40:24 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 12:48:48 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_PARSING_OPTIONS_H__
# define __NM_PARSING_OPTIONS_H__

# include "nm.h"

enum				e_needargs {
	no_argument,
	required_argument
};

typedef struct			s_options {
	char			*longname;
	size_t			flag;
	int			has_arg;
	int			shortname;
}				t_options;

int				ft_parse_options(struct s_file *, int, char const **);

#endif /* __NM_PARSING_OPTIONS_H__ */
