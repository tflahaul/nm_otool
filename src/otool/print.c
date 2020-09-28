/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 18:04:28 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/28 12:12:46 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/file.h"
#include "../../include/otool.h"
#include "../../include/bytes.h"
#include "../../include/errors.h"
#include "../../include/arguments.h"
#if defined __APPLE__
# include <mach-o/loader.h>
#else
# error "Systems other than macOS are not supported"
#endif /* __APPLE */
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static inline void		print_context(struct machsect *mach, struct arguments *args)
{
	printf("%s:\n", args->arguments[args->idx]);
	printf("Contents of (__TEXT,%s) section\n", mach->target);
}

static void			print_text_section(struct machsect *mach, struct arguments *args)
{
	unsigned int		idx;
	char const		*format = __is_64_bytes(mach->magic) ? "%016lx\t" : "%08lx\t";
	uintptr_t		address = __is_64_bytes(mach->magic) ? BASE_ADDRESS : 0x0UL;

	print_context(mach, args);
	for (register unsigned int index = 0; index < mach->section.length; index += 16) {
		idx = 0;
		printf(format, (address + mach->offset + index));
		while (idx < (mach->section.length - index < 16 ? mach->section.length - index : 16))
			printf("%02x ", ((uint8_t *)mach->section.head)[index + idx++]);
		puts("");
	}
}

static void			print_strings_section(struct machsect *mach, struct arguments *args)
{
	unsigned int		index = 0;
	char			*offset = (char *)mach->section.head;

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

void				print_target_section(struct machsect *mach, struct arguments *args)
{
	if (args->options & OPTION_S)
		print_strings_section(mach, args);
	else
		print_text_section(mach, args);
}
