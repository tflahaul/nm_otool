/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 09:30:47 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 12:53:05 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/nm.h"
#include "include/nm_symlist.h"

#define EXIT_FALSE	0
#define EXIT_TRUE	1

static int			ft_strcmp(char const *s1, char const *s2)
{
	if (s1 == s2)
		return (EXIT_FALSE);
	while (*s1 && *s2)
		if (*s1++ != *s2++)
			return (*(s1 - 1) - *(s2 - 1));
	return ((*s1) - (*s2));
}

static inline int		ft_alpha_cmp(	struct s_file *file,
						struct s_list *pos)
{
	char const		*s1 = ft_get_name(file, pos);
	char const		*s2 = ft_get_name(file, pos->next);

	return (ft_strcmp(s1, s2) > 0 ? EXIT_FALSE : EXIT_TRUE);
}

static void			ft_swap_nodes(	struct s_list *head,
						struct s_list *prev,
						struct s_list *next)
{
	struct s_list		*node;

	node = prev->next;
	prev->next = next->next;
	next->next = node;
	if (prev->next != head)
		prev->next->prev = prev;
	if (next->next != head)
		next->next->prev = next;
	node = prev->prev;
	prev->prev = next->prev;
	next->prev = node;
	if (prev->prev != head)
		prev->prev->next = prev;
	next->prev->next = next;
}

/*
**	Does a bubble sort on the given list. Sorting time is O(n^2) on average
**	which is slow but sufficient in most cases.
*/
void				ft_bubble_sort_list(	struct s_file *file,
							struct s_symlist *lst)
{
	struct s_list		*position;

	if (file->flags & OPTION_P)
		return ;
	position = &(lst->list);
	while ((position = position->next) != &(lst->list))
	{
		if (position->next != &(lst->list) && ft_alpha_cmp(file, position)) {
			ft_swap_nodes(&(lst->list), position, position->next);
			position = position->next;
		}
	}
}
