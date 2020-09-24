/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:25:24 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/24 16:35:06 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/sections.h"
#include "../../include/arguments.h"
#include "../../include/bytes.h"
#if defined __APPLE__
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
#else
# error "Systems other than macOS are not supported"
#endif /* __APPLE */
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

static inline void	print_nspaces(int x)
{
	char		buffer[256];

	memset(buffer, ' ', sizeof(buffer));
	buffer[256 - 1] = 0;
	write(STDOUT_FILENO, buffer, (size_t)x);
}

static struct msection	*find_section(struct msection *head, uint32_t id)
{
	while (head != NULL) {
		if (head->id == id)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static inline int	get_char_from_section(struct msection *section)
{
	if (section == NULL)
		return ('?');
	if (strcmp(section->sectname, SECT_TEXT) == 0)
		return ('t');
	if (strcmp(section->sectname, SECT_DATA) == 0)
		return ('d');
	if (strcmp(section->sectname, SECT_BSS) == 0)
		return ('b');
	return ('s');
}

static int		get_type_character(struct symbol *sym, struct machobj *m)
{
	int		type = '?';

	if ((sym->type & N_TYPE) == N_UNDF)
		type = ((sym->value == 0) ? 'u' : 'c');
	else if ((sym->type & N_TYPE) == N_PBUD)
		type = 'u';
	else if ((sym->type & N_TYPE) == N_ABS)
		type = 'a';
	else if ((sym->type & N_TYPE) == N_INDR)
		type = 'i';
	else if ((sym->type & N_TYPE) == N_SECT)
		type = get_char_from_section(find_section(m->sections_list, sym->sectid));
	if (type != '?' && (sym->type & N_EXT))
		type = type + ('A' - 'a');
	return (type);
}

static void		print_node(struct machobj *m, struct symbol *sym, size_t opt)
{
	if (!(opt & OPTION_J)) {
		if (sym->value != 0 || (sym->value == 0 && (sym->type & N_TYPE) != N_UNDF))
			printf(__is_64_bytes(m->magic) ? "%016llx " : "%08llx ", sym->value);
		else
			__is_64_bytes(m->magic) ? print_nspaces(17) : print_nspaces(9);
		printf("%c ", get_type_character(sym, m));
	}
	puts(sym->name);
}

void			print_symbols(struct file *f, struct machobj *m, size_t opt)
{
	struct symbol	*root = m->symbols_root;

	if (root != NULL) {
		print_tree(root->left);
		print_node(m, root, opt);
		print_tree(root->right);
	}
}
