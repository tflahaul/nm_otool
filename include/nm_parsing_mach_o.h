/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_parsing_mach_o.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:23 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 13:05:13 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_PARSING_MACH_O_H__
# define __NM_PARSING_MACH_O_H__

# include "nm.h"

int			ft_load_file_content(struct s_file *, char const *);
int			ft_parse_mach_o_file(struct s_file *);
void			ft_display_symbols(struct s_file *);

#endif /* __NM_PARSING_MACH_O_H__ */
