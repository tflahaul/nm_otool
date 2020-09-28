/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:34:05 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/28 11:08:44 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"
#include "../../include/otool.h"
#include "../../include/errors.h"
#include <stdint.h>
#include <stdio.h>

#define __is_print(x)	(x > 32 && x < 127)

int				print_strings(struct file *object)
{
	char			*offset = (char *)object->head;
	char			*temp;

	while ((uintptr_t)offset <= ((uintptr_t)object->head + object->length)) {
		temp = offset;
		while (__is_print(*offset))
			++offset;
		if ((uintptr_t)offset - (uintptr_t)temp >= MIN_LENGTH)
			puts(temp);
		++offset;
	}
	return (EXIT_SUCCESS);
}
