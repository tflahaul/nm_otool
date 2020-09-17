/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:17 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/17 15:48:59 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_H__
# define __NM_H__

# if defined __APPLE__
#  include <mach-o/loader.h>
#  include <mach-o/swap.h>
#  include <mach-o/fat.h>
#  include <mach-o/nlist.h>
#  define __is_universal(x)	(x == FAT_MAGIC || x == FAT_CIGAM)
#  define __is_supported(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64 || x == MH_MAGIC || x == MH_CIGAM)
#  define __is_64_bytes(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64)
# else
#  error "Systems other than macOS are not supported"
# endif /* __APPLE__ */

# include <stdint.h>
# include <unistd.h>

struct			symbol
{
	char		*name;
	struct nlist_64	*entry;
};

struct			machobj
{
	struct msection	*sections_list;
	struct symbol	*symbols_array;
	uint64_t	arrsize;
	uint32_t	magic;
	void		*strtab;
	void		*offset;
};

struct			file
{
	void		*head;
	uintptr_t	length;
};

int		load_file_informations(struct file *, char const *);
int		list_symbols_from_file(struct file *, size_t);

#endif /* __NM_H__ */
