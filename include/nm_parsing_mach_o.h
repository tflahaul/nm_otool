/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_parsing_mach_o.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:23 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/27 12:38:14 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_PARSING_MACH_O_H__
# define __NM_PARSING_MACH_O_H__

# include "nm.h"

int			ft_parse_architecture(struct s_file *);
int			ft_load_file_content(struct s_file *, char const *);
void			ft_display_symbols(struct s_mach_section *, struct s_file *);
void			ft_parse_segment(struct s_mach_section *, void *);
void			ft_parse_mach_section(struct s_file *, uintptr_t);

#endif /* __NM_PARSING_MACH_O_H__ */
