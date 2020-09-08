/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   architecture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 09:33:27 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/08 19:26:32 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/errors.h"
#include "../../include/memory.h"
#include <stdint.h>
#include <stdio.h>

int			architecture_dispatch(struct s_file_infos *file)
{
	uint32_t const	magic = read_u32(file, (uintptr_t)file->head);

//	if (magic == FAT_CIGAM || magic == FAT_MAGIC || magic == FAT_CIGAM_64 || magic == FAT_MAGIC_64)
//		get macho section from FAT
//	parse macho section
	printf("%#x\n", magic);
	return (EXIT_SUCCESS);
}
