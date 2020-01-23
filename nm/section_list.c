/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 14:17:22 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/23 15:24:26 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../include/nm_parsing_sections.h"

void			ft_push_sect(struct s_section **head, struct s_section *node)
{
	if (head == NULL || *head == NULL)
		*head = node;
	else {
		node->next = *head;
		*head = node;
	}
}
