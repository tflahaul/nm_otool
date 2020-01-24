/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:17:22 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/24 15:38:09 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/nm_parsing_sections.h"

void			ft_push_sect(struct s_section **head, struct s_section *node)
{
	if (head == NULL || *head == NULL) {
		if (node != NULL)
			node->id = 1;
		*head = node;
	}
	else {
		node->id = (*head)->id + 1;
		node->next = *head;
		*head = node;
	}
}

void			ft_free_list(struct s_section *head)
{
	struct s_section	*node = head;

	while (head != NULL) {
		node = head->next;
		free((void *)head);
		head = node;
	}
}
