/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:53 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/13 18:55:16 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/memory.h"
#include "../../include/nm.h"
#include <stdint.h>

uint32_t		safe_read_u32(struct s_file_infos *f, uintptr_t ptr)
{
	return (__readable(f, ptr, uint32_t) ? ((uint32_t *)ptr)[0] : 0);
}

uint64_t		safe_read_u64(struct s_file_infos *f, uintptr_t ptr)
{
	return (__readable(f, ptr, uint64_t) ? ((uint64_t *)ptr)[0] : 0);
}
