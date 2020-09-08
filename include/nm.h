/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:17 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/08 19:26:20 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __NM_H__
# define __NM_H__

# if defined __APPLE__
#  include <mach-o/loader.h>
#  include <mach-o/swap.h>
#  include <mach-o/fat.h>
#  include <mach-o/nlist.h>
//# else
//#  error "Systems other than macOS are not supported"
# endif /* __APPLE__ */

# include <stdint.h>

struct				s_symbol
{
	char			*name;
	struct nlist_64		*entry;
};

#pragma pack(push, 4)

struct				s_mach_section
{
	struct s_section	*sectlist;
	struct s_symbol		*symarray;
	uint64_t		arrsize;
	uint32_t		magic;
	void			*strtab;
	void			*offset;
};

#pragma pack(pop)

struct				s_file_infos
{
	void			*head;
	uintptr_t		length;
};

int		map_into_memory(struct s_file_infos *, char const *);
int		architecture_dispatch(struct s_file_infos *);

#endif /* __NM_H__ */
