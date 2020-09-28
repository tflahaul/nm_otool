/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:34:14 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/28 10:42:57 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OTOOL_H__
# define __OTOOL_H__

# if defined __APPLE__
#  include <mach-o/loader.h>
# else
#  error "Systems other than macOS are not supported"
# endif /* __APPLE */

# include "file.h"
# include "arguments.h"
# include <unistd.h>
# include <stdint.h>

# define BASE_ADDRESS	(0x100000000)

/* Minimum length of sequence of graphic chars to trigger output */
# define MIN_LENGTH	4

# pragma pack(push, 4)
struct			machsect
{
	struct file	object;
	struct file	section;
	uint32_t	magic;
	uint32_t	offset;
};
# pragma pack(pop)

int			load_file_informations(struct file *, char const *);
int			print_strings(struct file *);
int			print_section(struct file *, struct arguments *);
int			get_section_x86_64(struct machsect *);
int			get_section_i386(struct machsect *);
void			print_text_section(struct machsect *, struct arguments *);

#endif /* __OTOOL_H__ */
