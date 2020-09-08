/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:53 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/08 19:27:55 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include <stdint.h>

uint32_t		read_u32(struct s_file_infos *f, uintptr_t ptr)
{
	if (ptr >= (uintptr_t)f->head && ptr <= (uintptr_t)f->head + f->length - sizeof(uint32_t))
		return (((uint32_t *)ptr)[0]);
	return (0);
}

uint64_t		read_u64(struct s_file_infos *f, uintptr_t ptr)
{
	if (ptr >= (uintptr_t)f->head && ptr <= (uintptr_t)f->head + f->length - sizeof(uint64_t))
		return (((uint64_t *)ptr)[0]);
	return (0);
}
