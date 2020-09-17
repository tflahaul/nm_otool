/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:53 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/17 16:27:01 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/memory.h"
#include "../../include/nm.h"
#include <stdint.h>

uint32_t		safe_read_u32(struct file *f, uintptr_t ptr)
{
	return (__readable(f, ptr, uint32_t) ? ((uint32_t *)ptr)[0] : 0);
}

uint64_t		safe_read_u64(struct file *f, uintptr_t ptr)
{
	return (__readable(f, ptr, uint64_t) ? ((uint64_t *)ptr)[0] : 0);
}

uint32_t		swap_uint32(uint32_t x)
{
	return (((x & 0xff000000) >> 24) | ((x & 0x00ff0000) >> 8) |\
		((x & 0x0000ff00) << 8) | ((x & 0x000000ff) << 24));
}
