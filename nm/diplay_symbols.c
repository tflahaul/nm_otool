/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diplay_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:40:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 13:33:41 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../include/nm.h"
#include "../include/nm_parsing_options.h"

void			ft_display_symbols(struct s_file *file)
{
	if (file->flags & OPTION_R) {
		for (unsigned int index = file->arrsize; index > 0; --index)
			printf("%s\n", file->symarray[index].name);
	}
	else {
		for (unsigned int index = 0; index < file->arrsize; ++index)
			printf("%s\n", file->symarray[index].name);
	}
}
