/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 18:04:28 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/29 12:08:03 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"
#include "../../include/otool.h"
#include "../../include/bytes.h"
#include "../../include/errors.h"
#include "../../include/arguments.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static inline void	print_context(struct machsect *mach, struct arguments *args)
{
	printf("%s:\n", args->arguments[args->idx]);
	printf("Contents of (__TEXT,%s) section\n", mach->target);
}

void			print_text_section(struct machsect *mach, struct arguments *args)
{
	unsigned int	idx;
	char const	*format = __is_64_bytes(mach->magic) ? "%016lx\t" : "%08lx\t";
	uintptr_t	address = __is_64_bytes(mach->magic) ? BASE_ADDRESS : 0x0UL;

	print_context(mach, args);
	for (register unsigned int index = 0; index < mach->section.length; index += 16) {
		idx = 0;
		printf(format, (address + mach->offset + index));
		while (idx < (mach->section.length - index < 16 ? mach->section.length - index : 16))
			printf("%02x ", ((uint8_t *)mach->section.head)[index + idx++]);
		puts("");
	}
}

void			print_strings_section(struct machsect *mach, struct arguments *args)
{
	unsigned int	index = 0;
	char		*offset = (char *)mach->section.head;

	print_context(mach, args);
	while (index < mach->section.length) {
		while (offset[index] != 0) {
			printf("%c", __is_print(offset[index]) ? offset[index] : ' ');
			++index;
		}
		puts("");
		++index;
	}
}
