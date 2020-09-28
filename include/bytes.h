/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:26 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/28 09:20:05 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BYTES_H__
# define __BYTES_H__

# include "file.h"
# include <stdint.h>
# include <unistd.h>

# define __end_addr(f)		((uintptr_t)(f)->head + (f)->length)

uint32_t		swap_uint32(uint32_t);
uint32_t		safe_read_u32(struct file *, void *);
uint64_t		safe_read_u64(struct file *, void *);
int			__is_readable(struct file *, void *, size_t);

#endif /* __BYTES_H__ */
