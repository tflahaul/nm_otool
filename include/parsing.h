/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 18:14:11 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/17 15:05:25 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSING_H__
# define __PARSING_H__

# include "nm.h"

int		get_symbols_x86_64(struct file *, struct machobj *);
int		get_symbols_i386(struct file *, struct machobj *);

#endif /* __PARSING_H__ */
