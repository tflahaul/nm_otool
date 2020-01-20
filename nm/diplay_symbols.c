/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diplay_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:40:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 16:00:37 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../include/nm.h"
#include "../include/nm_parsing_options.h"

static inline void	ft_names_only(struct s_symbol *entry)
{
	printf("%s\n", entry->name);
}

static inline void	ft_complete_print(struct s_symbol *entry)
{
	unsigned int	type;

	if (entry->entry->n_value == 0)
		printf("                 ");
	else
		printf("%016llx ", entry->entry->n_value);

	switch (entry->entry->n_type & N_TYPE)
	{
	case N_UNDF:
		if (entry->entry->n_value != 0)
			type = 'c';
		else
			type = 'U';
		break;
	case N_PBUD:
		type = 'u';
		break;
	case N_ABS:
		type = 'a';
		break;
	case N_SECT:
		type = 't';
		break;
	case N_INDR:
		type = 'i';
		break;
	default:
		type = '?';
		break;
	}
	printf("%c %s\n", type, entry->name);
}

void			ft_display_symbols(struct s_file *file)
{
	void		(*funptr)(struct s_symbol *);

	if (file->symarray == NULL)
		return ;
	funptr = (file->flags & OPTION_J ? &ft_names_only : &ft_complete_print);
	if (file->flags & OPTION_R) {
		while (file->arrsize--)
			(*funptr)(&(file->symarray[file->arrsize]));
	}
	else {
		for (unsigned int index = 0; index < file->arrsize; ++index)
			(*funptr)(&(file->symarray[index]));
	}
}
