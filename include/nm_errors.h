/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:32:14 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_ERRORS_H__
# define __NM_ERRORS_H__

# include <stdlib.h>
# include <stdio.h>

static inline void		ft_assert(int x, char const *file, int line)
{
	if (__builtin_expect(((x) < EXIT_SUCCESS), 0)) {
		fprintf(stderr, "Error: %s:%i\n", file, line);
		exit(EXIT_FAILURE);
	}
}

# define HANDLE_GNU_ERROR(x)	{ ft_assert((x), __FILE__, __LINE__); }

#endif /* __NM_ERRORS_H__ */
