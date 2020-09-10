/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diplay_symbols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 14:40:04 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/29 12:16:14 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../include/nm.h"
#include "../include/nm_parsing_options.h"
#include "../include/nm_parsing_sections.h"

#define FORMAT		"%c %s\n"

static struct s_section		*ft_find_section(struct s_section *head, uint8_t id)
{
	struct s_section	*node = head;

	while (node != NULL) {
		if (node->id == (int)id)
			return (node);
		node = node->next;
	}
	return (NULL);
}

static int		ft_get_char(	struct s_section *section	)
{
	int		ret;
	char		*name;

	if (section == NULL)
		return ('?');
	if (section->architecture == LC_SEGMENT_64)
		name = ((struct section_64 *)section->offset)->sectname;
	else
		name = ((struct section *)section->offset)->sectname;
	if (strcmp(name, SECT_TEXT) == 0)
		ret = 'T';
	else if (strcmp(name, SECT_DATA) == 0)
		ret = 'D';
	else if (strcmp(name, SECT_BSS) == 0)
		ret = 'B';
	else
		ret = 'S';
	return (ret);
}

static inline void	ft_putendl(	__unused struct s_file *file,
					__unused struct s_mach_section *mach,
					struct s_symbol *entry	)
{
	write(STDOUT_FILENO, entry->name, strlen(entry->name));
	write(STDOUT_FILENO, "\n", 1);
}

static void		ft_complete_print(	struct s_file *file,
						struct s_mach_section *mach,
						struct s_symbol *entry)
{
	int		type;

	if ((entry->entry->n_type & N_TYPE) == N_UNDF) {
		if ((mach->magic == MH_MAGIC_64 || mach->magic == MH_CIGAM_64) && entry->entry->n_value != 0)
			type = 'c';
		else if ((mach->magic == MH_MAGIC || mach->magic == MH_CIGAM) && (uint32_t)entry->entry->n_value != 0)
			type = 'c';
		else
			type = 'U';
	}
	else if ((entry->entry->n_type & N_TYPE) == N_PBUD)
		type = 'u';
	else if ((entry->entry->n_type & N_TYPE) == N_ABS)
		type = 'A';
	else if ((entry->entry->n_type & N_TYPE) == N_INDR)
		type = 'I';
	else if ((entry->entry->n_type & N_TYPE) == N_SECT) {
		type = ft_get_char(ft_find_section(mach->sectlist, entry->entry->n_sect));
		if (type != '?' && !(entry->entry->n_type & N_EXT))
			type -= ('A' - 'a');
	}
	else
		type = '?';
	if (!(file->flags & OPTION_U) || type == 'U') {
		if (mach->magic == MH_MAGIC_64 || mach->magic == MH_CIGAM_64) {
			if (entry->entry->n_value == 0 && (entry->entry->n_type & N_TYPE) == N_UNDF)
				printf("                 ");
			else
				printf("%016llx ", entry->entry->n_value);
		}
		else {
			if ((uint32_t)entry->entry->n_value == 0 && (entry->entry->n_type & N_TYPE) == N_UNDF)
				printf("         ");
			else
				printf("%08x ", (uint32_t)entry->entry->n_value);
		}
		printf(FORMAT, type, entry->name);
	}
}

void				ft_display_symbols(	struct s_mach_section *mach,
							struct s_file *file)
{
	void		(*funptr)(struct s_file *, struct s_mach_section *, struct s_symbol *);

	if (mach->symarray == NULL)
		return ;
	funptr = (file->flags & OPTION_J) ? &ft_putendl : &ft_complete_print;
	if ((file->flags & OPTION_R) && !(file->flags & OPTION_P)) {
		while (mach->arrsize--)
			(*funptr)(file, mach, &(mach->symarray[mach->arrsize]));
	}
	else {
		for (unsigned int index = 0; index < mach->arrsize; ++index)
			(*funptr)(file, mach, &(mach->symarray[index]));
	}
}
