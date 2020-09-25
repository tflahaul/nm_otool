/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:34:14 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/25 16:56:51 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OTOOL_H__
# define __OTOOL_H__

# if defined __APPLE__
#  include <mach-o/loader.h>
# else
#  error "Systems other than macOS are not supported"
# endif /* __APPLE */

# include "nm.h"
# include "file.h"
# include <unistd.h>

# define BASE_ADDRESS	(0x100000000)

/* Minimum length of sequence of graphic chars to trigger output */
# define MIN_LENGTH	4

void			print_strings(struct machobj *);
void			print_text_section(struct machobj *, struct section_64 *);
int			get_section_x86_64(struct machobj *);
int			get_section_i386(struct machobj *);
int			print_section(struct file *, size_t);

#endif /* __OTOOL_H__ */
