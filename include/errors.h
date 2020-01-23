/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/23 12:43:43 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ERRORS_H__
# define __ERRORS_H__

# include <stdlib.h>
# include <stdio.h>

# define EXIT_FALSE	0
# define EXIT_TRUE	1

static inline void		ft_assert(int x, char const *file, int line)
{
	if (__builtin_expect(((x) < EXIT_SUCCESS), 0)) {
		fprintf(stderr, "Error: %s:%i\n", file, line);
		exit(EXIT_FAILURE);
	}
}

static inline void		ft_free_on_error(int used, void *ptr)
{
	if (used > 0)
		free((void *)ptr);
}

# define HANDLE_GNU_ERROR(x)		{ ft_assert((x), __FILE__, __LINE__); }
# define FREE_ON_ERROR(used, ptr)	{ ft_free_on_error((used), (ptr)); }

#endif /* __ERRORS_H__ */
