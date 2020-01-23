/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_parsing_sections.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:10:41 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/23 16:05:54 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_PARSING_SECTIONS_H__
# define __NM_PARSING_SECTIONS_H__

/*
**	@architecture:	LC_SEGMENT or LC_SEGMENT_64
**	@offset:	Section header offset
*/
struct				s_section
{
	int			id;
	int			architecture;
	void			*offset;
	struct s_section	*next;
};

void			ft_free_list(struct s_section *);
void			ft_push_sect(struct s_section **, struct s_section *);

#endif /* __NM_PARSING_SECTIONS_H__ */
