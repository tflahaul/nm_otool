/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 11:27:03 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:56:13 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "include/nm_symlist.h"

static struct s_symlist		*ft_malloc_new_node(struct nlist_64 *entry)
{
	struct s_symlist	*node;

	if ((node = (struct s_symlist *)malloc(sizeof(struct s_symlist))) == NULL)
		return (NULL);
	node->entry.entry64 = entry;
	ft_list_init_head(&(node->list));
	return (node);
}

int				ft_symlist_push(struct s_symlist *head,
						struct nlist_64 *entry)
{
	struct s_symlist	*node;

	if ((node = ft_malloc_new_node(entry)) == NULL)
		return (-EXIT_FAILURE);
	ft_list_push(&(node->list), &(head->list));
	return (EXIT_SUCCESS);
}

/*
**	These are easy-to-use, highly portable functions for manipulating
**	circular linked lists. This implementation comes from the Linux
**	kernel source tree, file `include/linux/list.h`
*/
void				ft_list_init_head(struct s_list *head)
{
	head->next = head;
	head->prev = head;
}

/*
**	Insert a new entry between two known consecutive entries (prev & next).
**	This is only for internal list manipulation where we know the `prev`
**	and `next` pointers.
*/
void				ft_list_add(	struct s_list *node,
						struct s_list *prev,
						struct s_list *next	)
{
	next->prev = node;
	node->next = next;
	node->prev = prev;
	prev->next = node;
}

/*
**	Insert a new entry AFTER the specified head. This is good for
**	implementing stacks.
*/
void				ft_list_push(struct s_list *node, struct s_list *head)
{
	ft_list_add(node, head, head->next);
}

void				ft_free_list(struct s_list *head)
{
	struct s_list		*node;
	struct s_list		*next;

	node = head->next;
	next = node->next;
	while (node != head)
	{
		free((void *)((uintptr_t)node - __offsetof(struct s_symlist, list)));
		node = next;
		next = node->next;
	}
}
