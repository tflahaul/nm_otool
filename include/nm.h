/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:17 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/28 09:49:38 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_H__
# define __NM_H__

# if defined __APPLE__
#  include <mach-o/loader.h>
#  include <mach-o/nlist.h>
#  define __is_universal(x)	(x == FAT_MAGIC || x == FAT_CIGAM)
#  define __is_supported(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64 || x == MH_MAGIC || x == MH_CIGAM)
#  define __is_64_bytes(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64)
# else
#  error "Systems other than macOS are not supported"
# endif /* __APPLE__ */

# include "arguments.h"
# include "file.h"
# include <stdint.h>
# include <unistd.h>

# pragma pack(push, 4)

struct			symbol
{
	uint32_t	type;
	uint32_t	sectid;
	uint64_t	value;
	char		*name;
	struct symbol	*right;
	struct symbol	*left;
};

struct			machobj
{
	struct msection	*sections_list;
	struct symbol	*symbols_root;
	void		*strtab;
	struct file	object;
	uint32_t	magic;
};

# pragma pack(pop)

int		load_file_informations(struct file *, char const *);
int		list_symbols_from_file(struct file *, struct arguments *);
int		get_symbols_i386(struct machobj *);
int		get_symbols_x86_64(struct machobj *);
int		insert_symbol(struct machobj *, void *);
void		print_symbols(struct machobj *, struct arguments *);
void		btree_free(struct symbol *);

#endif /* __NM_H__ */
