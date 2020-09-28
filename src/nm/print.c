/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:25:24 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/28 09:17:20 by thflahau         ###   ########.fr       */
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

static void		print_node(struct machobj *mach, struct symbol *sym, size_t opt)
{
	if (!(opt & OPTION_J)) {
		if (sym->value != 0 || (sym->value == 0 && (sym->type & N_TYPE) != N_UNDF)) {
			printf(__is_64_bytes(mach->magic) ? "%016llx " : "%08llx ", sym->value);
		} else {
			printf("%*c", __is_64_bytes(mach->magic) ? 17 : 9, ' ');
		}
		printf("%c ", get_type_character(sym, mach));
	}
	puts(sym->name);
}

void			print_symbols(struct machobj *mach, struct arguments *args)
{
	struct symbol	*root = mach->symbols_root;
	struct symbol	*prev = NULL;

	if (args->size > 1)
		printf("\n%s:\n", args->arguments[args->idx]);
	while (root != NULL) {
		if (root->left != NULL) {
			prev = root->left;
			while (prev->right != NULL && prev->right != root)
				prev = prev->right;
			if (prev->right == NULL) {
				prev->right = root;
				root = root->left;
			} else {
				prev->right = NULL;
				print_node(mach, root, args->options);
				root = root->right;
			}
		} else {
			print_node(mach, root, args->options);
			root = root->right;
		}
	}
}
