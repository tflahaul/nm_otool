/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diplay_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:40:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:56:38 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "include/nm.h"
#include "include/nm_symlist.h"

static inline struct s_symlist	*ft_get_entry(struct s_list *ptr)
{
	return ((struct s_symlist *)((uintptr_t)ptr - __offsetof(struct s_symlist, list)));
}

void			ft_display_symbols(struct s_file *file, struct s_symlist *lst)
{
	struct s_list	*position;

	position = &(lst->list);
	while ((position = position->next) != &(lst->list))
	printf("%s\n", (char *)(uintptr_t)file->strtab + ft_get_entry(position)->entry.entry64->n_un.n_strx);
}
