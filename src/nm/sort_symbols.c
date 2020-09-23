/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:49:38 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/23 19:34:34 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/arguments.h"
#include "../../include/errors.h"
#include "../../include/bytes.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

static inline struct symbol	*push_front(struct symbol *node, struct symbol *prev)
{
	struct symbol		*ptr = node->next;

	node->next = prev;
	prev->next = ptr;
	return (node);
}

static inline int		compare_names(struct file *f, struct machobj *m, struct symbol *a, struct symbol *b)
{
	char const		*str_a = (char const *)((uintptr_t)m->strtab + a->stridx);
	char const		*str_b = (char const *)((uintptr_t)m->strtab + b->stridx);

	if (__readable(f, str_a, uint16_t) == TRUE && __readable(f, str_b, uint16_t) == TRUE)
		return (strcmp(str_a, str_b));
	return (-EXIT_FAILURE);
}

static void			bubble_sort_symbols(struct file *f, struct machobj *m)
{
	struct symbol		*ptr = m->symbols_list;

	while (ptr->next != NULL) {
		if (compare_names(f, m, ptr, ptr->next) < 0) {
			ptr = push_front(ptr->next, ptr);
		}
		else { ptr = ptr->next; }
	}
}

void				sort_symbols(struct file *f, struct machobj *m, size_t opt)
{
	if (!(opt & OPTION_P)) {
		bubble_sort_symbols(f, m);
	}
}
