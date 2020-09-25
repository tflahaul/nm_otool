/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 18:04:28 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/25 15:24:29 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/otool.h"
#include "../../include/bytes.h"
#include "../../include/errors.h"
#if defined __APPLE__
# include <mach-o/loader.h>
#else
# error "Systems other than macOS are not supported"
#endif /* __APPLE */
#include <stdint.h>
#include <stdio.h>

void				print_text_section(struct file *f, struct section_64 *section)
{
	struct file		text_section;

	text_section.head = (void *)((uintptr_t)f->head + section->offset);
	text_section.length = section->size;
	puts("[file]:");
	puts("Contents of (__TEXT,__text) section");
	if (__readable(f, text_section.head, section->size) == TRUE) {
		for (register unsigned int index = 0; index < section->size; index += 16) {
			printf("%016lx\t", (BASE_ADDRESS + section->offset + index));
			for (register unsigned int idx = 0; idx < 16; ++idx)
				printf("%02x ", ((uint8_t *)text_section.head)[index + idx]);
			puts("");
		}
	}
}
