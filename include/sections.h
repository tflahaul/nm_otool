/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:10:41 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/24 15:55:48 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SECTIONS_H__
# define __SECTIONS_H__
# if defined __APPLE__
#  include <mach-o/loader.h>
# else
#  error "Systems other than macOS are not supported"
# endif /* __APPLE */
# include <stdint.h>

#pragma pack(push, 4)

struct			msection
{
	uint32_t	id;
	char		sectname[16];
	struct msection	*next;
};

#pragma pack(pop)

int			push_section(struct msection **, struct section_64 *);
void			free_sections_list(struct msection *);

#endif /* __SECTIONS_H__ */
