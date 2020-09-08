/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:26 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/08 19:27:29 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MEMORY_H__
# define __MEMORY_H__

# include "nm.h"
# include <stdint.h>

uint32_t	read_u32(struct s_file_infos *f, uintptr_t ptr);
uint64_t	read_u64(struct s_file_infos *f, uintptr_t ptr);

#endif /* __MEMORY_H__ */
