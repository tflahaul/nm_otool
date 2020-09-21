/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 15:35:22 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/21 09:18:20 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/sections.h"
#include <mach-o/loader.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int			push_section(struct msection **head, struct section_64 *sect, uint32_t idx)
{
	struct msection	*node;

	if ((node = (struct msection *)malloc(sizeof(struct msection))) == NULL)
		return (-EXIT_FAILURE);
	memset(node->sectname, 0, sizeof(node->sectname));
	memcpy(node->sectname, sect->sectname, strnlen(sect->sectname, 15));
	node->next = (*head == NULL) ? NULL : *head;
	node->id = idx;
	*head = node;
	return (EXIT_SUCCESS);
}

void			free_sections_list(struct msection *head)
{
	struct msection	*ptr = head;

	while (head != NULL) {
		ptr = head->next;
		free((void *)head);
		head = ptr;
	}
}
