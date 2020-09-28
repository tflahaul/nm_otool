/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 19:27:26 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/28 09:55:59 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BYTES_H__
# define __BYTES_H__

# if defined __APPLE__
#  include <mach-o/loader.h>
#  define __is_universal(x)	(x == FAT_MAGIC || x == FAT_CIGAM)
#  define __is_supported(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64 || x == MH_MAGIC || x == MH_CIGAM)
#  define __is_64_bytes(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64)
# else
#  error "Systems other than macOS are not supported"
# endif /* __APPLE__ */

# include "file.h"
# include <stdint.h>
# include <unistd.h>

# define __end_addr(f)		((uintptr_t)(f)->head + (f)->length)

uint32_t		swap_uint32(uint32_t);
uint32_t		safe_read_u32(struct file *, void *);
uint64_t		safe_read_u64(struct file *, void *);
int			__is_readable(struct file *, void *, size_t);

#endif /* __BYTES_H__ */
