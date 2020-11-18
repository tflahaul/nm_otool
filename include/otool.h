/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 17:34:14 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/29 12:05:24 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OTOOL_H__
# define __OTOOL_H__

# include "file.h"
# include "arguments.h"
# include <unistd.h>
# include <stdint.h>

# define BASE_ADDRESS	(0x100000000)
# define __is_print(x)	(x > 32 && x < 127)

# pragma pack(push, 4)
struct			machsect
{
	char		*target;
	struct file	object;
	struct file	section;
	uint32_t	magic;
	uint32_t	offset;
};
# pragma pack(pop)

int			load_file_informations(struct file *, char const *);
int			print_section(struct file *, struct arguments *);
int			get_section_64(struct machsect *);
int			get_section_32(struct machsect *);
int			print_strings(struct file *);
void			print_strings_section(struct machsect *, struct arguments *);
void			print_text_section(struct machsect *, struct arguments *);

#endif /* __OTOOL_H__ */
