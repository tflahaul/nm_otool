/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:19:58 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/27 14:14:13 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "../include/errors.h"
#include "../include/nm.h"
#include "../include/nm_parsing_options.h"

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

static int		numeric_cmp(struct s_symbol *e1, struct s_symbol *e2)
{
	return (e1->entry->n_value > e2->entry->n_value);
}

static int		alpha_cmp(struct s_symbol *e1, struct s_symbol *e2)
{
	int const	ret = ft_strcmp(e1->name, e2->name);

	if (ret < 0)
		return (EXIT_FALSE);
	else if (ret > 0)
		return (EXIT_TRUE);
	return (numeric_cmp(e1, e2));
}

void			quicksort(	struct s_symbol *tab,
					int first,
					int last,
					int (*cmp)(struct s_symbol *, struct s_symbol *))
{
	int		i;
	int		j;
	int		pivot;
	struct s_symbol temp;

	if (first < last) {
		pivot = first;
		i = first;
		j = last;
		while (i < j) {
			while(!cmp(&(tab[i]), &(tab[pivot])) && i < last)
				i++;
			while (cmp(&(tab[j]), &(tab[pivot])))
				j--;
			if (i < j) {
				memcpy(&temp, &(tab[i]), sizeof(struct s_symbol));
				memcpy(&(tab[i]), &(tab[j]), sizeof(struct s_symbol));
				memcpy(&(tab[j]), &temp, sizeof(struct s_symbol));
			}
		}
		memcpy(&temp, &(tab[pivot]), sizeof(struct s_symbol));
		memcpy(&(tab[pivot]), &(tab[j]), sizeof(struct s_symbol));
		memcpy(&(tab[j]), &temp, sizeof(struct s_symbol));
		quicksort(tab, first, j - 1, cmp);
		quicksort(tab, j + 1, last, cmp);
	}
}

void			ft_quicksort_symbols(	struct s_mach_section *mach,
						struct s_file *file	)
{
	int		(*funptr)(struct s_symbol *, struct s_symbol *);

	if (mach->symarray == NULL || (file->flags & OPTION_P))
		return ;
	funptr = (file->flags & OPTION_N) ? &numeric_cmp : &alpha_cmp;
	quicksort(mach->symarray, 0, mach->arrsize - 1, funptr);
}
