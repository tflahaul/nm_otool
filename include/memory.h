/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:26 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/09 17:56:44 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MEMORY_H__
# define __MEMORY_H__

# include "nm.h"
# include <stdint.h>

# define END_ADDR(f)	((uintptr_t)f->head + f->length)

uint32_t		safe_read_u32(struct s_file_infos *, uintptr_t);
uint64_t		safe_read_u64(struct s_file_infos *, uintptr_t);

#endif /* __MEMORY_H__ */
