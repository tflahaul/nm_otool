/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/10 14:56:13 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ERRORS_H__
# define __ERRORS_H__

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

# define EXIT_FALSE		0
# define EXIT_TRUE		1

static inline void		ft_assert(int x, char const *err, char const *f, int l)
{
	if (__builtin_expect(((x) != EXIT_SUCCESS), 0)) {
		fprintf(stderr, "Error: %s:%i -> %s\n", f, l, err);
		exit(EXIT_FAILURE);
	}
}

# define HANDLE_NULL_ERROR(p, err)	{ft_assert(((p) == NULL), err, __FILE__, __LINE__);}
# define HANDLE_NEG_ERROR(x, err)	{ft_assert(((x) < 0), err, __FILE__, __LINE__);}
# define HANDLE_GNU_ERROR(x, err)	{ft_assert((x), err, __FILE__, __LINE__);}

#endif /* __ERRORS_H__ */
