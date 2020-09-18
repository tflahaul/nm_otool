/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:10:41 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/18 15:44:26 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SECTIONS_H__
# define __SECTIONS_H__

# include <mach-o/loader.h>
# include <stdint.h>

struct			msection
{
	uint32_t	id;
	char		sectname[16];
	struct section	*next;
};

int			push_section(struct msection *, struct section_64 *, uint32_t);
void			free_sections_list(struct msection *);

#endif /* __SECTIONS_H__ */
