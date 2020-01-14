/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_symlist.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 10:57:29 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:54:18 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_SYMLIST_H__
# define __NM_SYMLIST_H__

# include <mach-o/nlist.h>

struct				s_list
{
	struct s_list		*next;
	struct s_list		*prev;
};

struct				s_symlist
{
	struct s_list		list;
	union			u_entry {
		struct nlist	*entry32;
		struct nlist_64	*entry64;
	} entry;
};

int				ft_symlist_push(struct s_symlist *,
						struct nlist_64 *);

void				ft_list_init_head(struct s_list *);

void				ft_list_add(	struct s_list *,
						struct s_list *,
						struct s_list *);
void				ft_list_push(	struct s_list *,
						struct s_list *);

void				ft_free_list(	struct s_list *);

#endif /* __NM_SYMLIST_H__ */
