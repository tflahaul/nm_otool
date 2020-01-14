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

#include <stdio.h>

#include "include/nm.h"
#include "include/nm_symlist.h"

#define EXIT_FALSE	0
#define EXIT_TRUE	1
#define CMP(x, y)	(((ft_strcmp(x, y) < 0) ? EXIT_FALSE : EXIT_TRUE))

static inline struct s_symlist	*ft_get_entry(	__pure struct s_list *ptr)
{
	return ((struct s_symlist *)((uintptr_t)ptr - __offsetof(struct s_symlist, list)));
}

static char			*ft_get_name(	__pure struct s_file *f,
						__pure struct s_list *p)
{
	return ((char *)(uintptr_t)f->strtab + ft_get_entry(p)->entry.entry64->n_un.n_strx);
}

static int			ft_strcmp(char const *s1, char const *s2)
{
	if (s1 == s2)
		return (EXIT_FALSE);
	while (*s1 && *s2)
		if (*s1++ != *s2++)
			return (*(s1 - 1) - *(s2 - 1));
	return ((*s1) - (*s2));
}

static void			ft_swap_nodes(struct s_list *prev, struct s_list *next)
{
	prev->prev->next = next;
	next->next->prev = prev;
	prev->next = next->next;
	next->prev = prev->prev;
	next->next = prev;
	prev->prev = next;
}

void				ft_bubble_sort_list(	struct s_file *file,
							struct s_symlist *lst)
{
	struct s_list		*position;
	struct s_list		*head = &(lst->list);

	if (file->flags & OPTION_P)
		return ;
	position = head;
	while ((position = position->next) != head)
	{
		if (CMP(ft_get_name(file, position), ft_get_name(file, position->next))) {
			ft_swap_nodes(position, position->next);
		}
	}
}
