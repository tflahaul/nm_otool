/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 18:04:28 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/26 12:09:38 by thflahau         ###   ########.fr       */
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
#include <stdio.h>

void				print_text_section(struct machsect *mach, struct arguments *args)
{
	printf("%s:\n", args->arguments[args->idx]);
	puts("Contents of (__TEXT,__text) section");
	for (register unsigned int index = 0; index < mach->section.length; index += 16) {
		printf("%016lx\t", (BASE_ADDRESS + index)); // bad address
		for (register unsigned int idx = 0; idx < 16; ++idx)
			printf("%02x ", ((uint8_t *)mach->section.head)[index + idx]);
		puts("");
	}
}
