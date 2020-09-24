/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:34:14 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/24 11:00:15 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OTOOL_H__
# define __OTOOL_H__

# include "nm.h"
# include <unistd.h>
# if defined __APPLE__
#  include <mach-o/loader.h>
# else
#  error "Systems other than macOS are not supported"
# endif /* __APPLE */

int			print_section(struct file *, size_t);
void			print_text_section(struct file *, struct section_64 *);
int			get_section_x86_64(struct file *, struct machobj *);
int			get_section_i386(struct file *, struct machobj *);

#endif /* __OTOOL_H__ */
