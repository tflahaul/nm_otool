/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:23 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:41:47 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_PARSING_H__
# define __NM_PARSING_H__

# include "nm.h"
# include "nm_symlist.h"

int		ft_load_file_content(struct s_file *, char const *);
int		ft_parse_mach_o_file(struct s_symlist *, struct s_file *);

void		ft_bubble_sort_list(struct s_file *, struct s_symlist *);
void		ft_display_symbols(struct s_file *, struct s_symlist *);

#endif /* __NM_PARSING_H__ */
