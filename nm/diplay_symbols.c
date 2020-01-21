/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diplay_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:40:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/21 12:18:01 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../include/nm.h"
#include "../include/nm_parsing_options.h"

#define FORMAT		"%c %s\n"

static inline void	ft_putendl(struct s_symbol *entry)
{
	write(STDOUT_FILENO, entry->name, strlen(entry->name));
	write(STDOUT_FILENO, "\n", 1);
}

static inline void	ft_complete_print(struct s_symbol *entry)
{
	if (entry->entry->n_value == 0 && (entry->entry->n_type & N_TYPE) == N_UNDF)
		printf("                 ");
	else
		printf("%016llx ", entry->entry->n_value);
	if ((entry->entry->n_type & N_TYPE) == N_UNDF) {
		if (entry->entry->n_value != 0)
			printf(FORMAT, 'c', entry->name);
		else
			printf(FORMAT, 'U', entry->name);
	}
	else if ((entry->entry->n_type & N_TYPE) == N_PBUD)
		printf(FORMAT, 'u', entry->name);
	else if ((entry->entry->n_type & N_TYPE) == N_ABS)
		printf(FORMAT, 'A', entry->name);
	else if ((entry->entry->n_type & N_TYPE) == N_INDR)
		printf(FORMAT, 'I', entry->name);
	else if ((entry->entry->n_type & N_TYPE) == N_SECT)
		printf(FORMAT, 'T', entry->name);
	else
		printf(FORMAT, '?', entry->name);
}

void			ft_display_symbols(struct s_file *file)
{
	void		(*funptr)(struct s_symbol *);

	if (file->symarray == NULL)
		return ;
	funptr = (file->flags & OPTION_J ? &ft_putendl : &ft_complete_print);
	if ((file->flags & OPTION_R) && !(file->flags & OPTION_P)) {
		while (file->arrsize--)
			(*funptr)(&(file->symarray[file->arrsize]));
	}
	else {
		for (unsigned int index = 0; index < file->arrsize; ++index)
			(*funptr)(&(file->symarray[index]));
	}
}
