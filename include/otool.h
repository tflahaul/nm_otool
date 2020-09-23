/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:34:14 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/23 18:10:18 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OTOOL_H__
# define __OTOOL_H__

# include "nm.h"
# include <unistd.h>
# include <mach-o/loader.h>

int			print_section(struct file *, size_t);
void			print_text_section(struct file *, struct section_64 *);
int			get_section_x86_64(struct file *, struct machobj *);
int			get_section_i386(struct file *, struct machobj *);

#endif /* __OTOOL_H__ */
