/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:17 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/24 16:30:25 by thflahau         ###   ########.fr       */
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
	void		*offset;
	uint32_t	magic;
};

# pragma pack(pop)

struct			file
{
	void		*head;
	uintptr_t	length;
};

int		load_file_informations(struct file *, char const *);
int		list_symbols_from_file(struct file *, size_t);
int		insert_symbol(struct file *f, struct machobj *, struct nlist_64 *);
void		print_symbols(struct file *, struct machobj *, size_t);
void		btree_free(struct symbol *);

#endif /* __NM_H__ */
