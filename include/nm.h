/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:17 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/23 15:07:07 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_H__
# define __NM_H__

# if defined __APPLE__
#  include <mach-o/loader.h>
#  include <mach-o/swap.h>
#  include <mach-o/fat.h>
#  include <mach-o/nlist.h>
# else
#  error "Systems other than macOS are not supported"
# endif /* __APPLE__ */

# define PROGRAM_NAME(p)	(p ? p : "a.out")

struct				s_symbol
{
	char			*name;
	struct nlist_64		*entry;
};

struct				s_file
{
	struct s_section	*lsthead;
	struct s_symbol		*symarray;
	char			*filename;
	unsigned char		*content;
	void			*strtab;
	size_t			length;
	size_t			arrsize;
	size_t			flags;
};

int				ft_parse_fat(struct s_file *);
int				ft_parse_architecture(struct s_file *);
void				ft_bubble_sort_symbols(struct s_file *);
void				ft_parse_mach_o_file(struct s_file *, void *);

#endif /* __NM_H__ */
