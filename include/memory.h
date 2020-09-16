/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:26 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/16 17:49:33 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MEMORY_H__
# define __MEMORY_H__

# include "nm.h"
# include <stdint.h>

# define __end_addr(f)		((uintptr_t)f->head + f->length)
# define __readable(f, p, type)	((uintptr_t)p >= (uintptr_t)f->head && (uintptr_t)p <= __end_addr(f) - sizeof(type))

uint32_t		safe_read_u32(struct s_file_infos *, uintptr_t);
uint64_t		safe_read_u64(struct s_file_infos *, uintptr_t);
uint32_t		swap_uint32(uint32_t);

#endif /* __MEMORY_H__ */
