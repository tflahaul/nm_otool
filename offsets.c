/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offsets.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 21:20:43 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 21:20:43 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include "include/nm.h"
#include "include/nm_symlist.h"

struct s_symlist	*ft_get_entry(	__pure struct s_list *ptr)
{
	return ((struct s_symlist *)((uintptr_t)ptr - __offsetof(struct s_symlist, list)));
}

char			*ft_get_name(	__pure struct s_file *f,
					__pure struct s_list *p)
{
	return ((char *)(uintptr_t)f->strtab + ft_get_entry(p)->entry.entry64->n_un.n_strx);
}
