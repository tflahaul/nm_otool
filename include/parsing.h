/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:14:11 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/16 18:15:12 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSING_H__
# define __PARSING_H__

int		get_symbols_x86_64(struct s_file_infos *, struct s_macho_file *);
int		get_symbols_i386(struct s_file_infos *, struct s_macho_file *);

#endif /* __PARSING_H__ */
