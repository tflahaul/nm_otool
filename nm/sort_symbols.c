/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_symbols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 12:19:58 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 13:34:05 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

#include "../include/nm.h"
#include "../include/nm_parsing_options.h"

static void			ft_swap_entries(struct s_symbol *e1, struct s_symbol *e2)
{
	struct s_symbol		temp;

	memcpy(&temp, e1, sizeof(struct s_symbol));
	memcpy(e1, e2, sizeof(struct s_symbol));
	memcpy(e2, &temp, sizeof(struct s_symbol));
}

static int			ft_strcmp(char const *s1, char const *s2)
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

static inline int		alpha_cmp(char const *s1, char const *s2)
{
	return ((ft_strcmp(s1, s2) > 0) ? EXIT_FAILURE : EXIT_SUCCESS);
}

void				ft_bubble_sort_symbols(struct s_file *file)
{
	struct s_symbol		*tab = file->symarray;

	if (file->flags & OPTION_P)
		return ;
	if (file->flags & OPTION_N) {
		for (unsigned int idx = 0; idx < file->arrsize - 1;) {
			if (tab[idx].entry->n_value > tab[idx + 1].entry->n_value) {
				ft_swap_entries(&(tab[idx]), &(tab[idx + 1]));
				idx = 0;
			}
			else
				++idx;
		}
	}
	else {
		for (unsigned int idx = 0; idx < file->arrsize - 1;) {
			if (alpha_cmp(tab[idx].name, tab[idx + 1].name)) {
				ft_swap_entries(&(tab[idx]), &(tab[idx + 1]));
				idx = 0;
			}
			else
				++idx;
		}
	}
}
