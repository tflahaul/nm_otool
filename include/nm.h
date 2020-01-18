/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:17 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:41:54 by thflahau         ###   ########.fr       */
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

# define OPTION_R		0x0000001
# define OPTION_U		0x0000002
# define OPTION_CAPU		0x0000004
# define OPTION_J		0x0000008
# define OPTION_P		0x0000010
# define OPTION_N		0x0000020

struct				s_symbol
{
	char			*name;
	struct nlist_64		*entry;
};

struct				s_file
{
	struct s_symbol		*symarray;
	char			*filename;
	unsigned char		*content;
	void			*strtab;
	size_t			length;
	size_t			arrsize;
	size_t			flags;
};

#endif /* __NM_H__ */
