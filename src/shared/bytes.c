/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:53 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/28 09:19:46 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/bytes.h"
#include "../../include/file.h"
#include <stdint.h>
#include <unistd.h>

int			__is_readable(struct file *f, void *ptr, size_t sz)
{
	return (ptr >= f->head && ptr <= (void *)((uintptr_t)f->head + f->length - sz));
}

uint32_t		safe_read_u32(struct file *f, void *ptr)
{
	return (__is_readable(f, ptr, sizeof(uint32_t)) ? ((uint32_t *)ptr)[0] : 0);
}

uint64_t		safe_read_u64(struct file *f, void *ptr)
{
	return (__is_readable(f, ptr, sizeof(uint64_t)) ? ((uint64_t *)ptr)[0] : 0);
}

uint32_t		swap_uint32(uint32_t x)
{
	return (((x & 0xff000000) >> 24) | ((x & 0x00ff0000) >> 8) |\
		((x & 0x0000ff00) << 8) | ((x & 0x000000ff) << 24));
}
