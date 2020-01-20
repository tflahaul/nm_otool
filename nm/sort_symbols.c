/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:19:58 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 16:00:15 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "../include/nm.h"
#include "../include/nm_parsing_options.h"

#define EXIT_FALSE	0
#define EXIT_TRUE	1

static void		ft_swap_entries(struct s_symbol *e1, struct s_symbol *e2)
{
	struct s_symbol	temp;

	memcpy(&temp, e1, sizeof(struct s_symbol));
	memcpy(e1, e2, sizeof(struct s_symbol));
	memcpy(e2, &temp, sizeof(struct s_symbol));
}

static int		ft_strcmp(char const *s1, char const *s2)
{
	if (s1 == s2)
		return (EXIT_SUCCESS);
	if (s1 == NULL || s2 == NULL)
		return (EXIT_FAILURE);
	while (*s1 && *s2)
		if (*s1++ != *s2++)
			return (*(s1 - 1) - *(s2 - 1));
	return ((*s1) - (*s2));
}

static int		alpha_cmp(struct s_symbol *e1, struct s_symbol *e2)
{
	return ((ft_strcmp(e1->name, e2->name) > 0) ? EXIT_TRUE : EXIT_FALSE);
}

static int		numeric_cmp(struct s_symbol *e1, struct s_symbol *e2)
{
	return (e1->entry->n_value > e2->entry->n_value);
}

/*
**	Does a bubble sort on the symbol array. Sorting time is O(n^2) on
**	average which is slow but sufficient in most cases.
*/
void			ft_bubble_sort_symbols(struct s_file *file)
{
	int		(*funptr)(struct s_symbol *, struct s_symbol *);

	if (file->symarray == NULL || file->flags & OPTION_P)
		return ;
	funptr = file->flags & OPTION_N ? &numeric_cmp : &alpha_cmp;
	for (unsigned int idx = 0; idx < file->arrsize - 1;) {
		if ((*funptr)(&(file->symarray[idx]), &(file->symarray[idx + 1]))) {
			ft_swap_entries(&(file->symarray[idx]), &(file->symarray[idx + 1]));
			idx = 0;
		}
		else
			++idx;
	}
}
