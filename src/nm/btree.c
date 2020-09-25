/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 15:31:44 by thflahau          #+#    #+#             */
/*   Updated: 2020/09/25 16:39:39 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/nm.h"
#include "../../include/bytes.h"
#include "../../include/errors.h"
#if defined __APPLE__
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
#else
# error "Systems other than macOS are not supported"
#endif /* __APPLE__ */
#include <stdlib.h>
#include <string.h>

static inline char	*safe_get_name(struct machobj *mach, uint32_t index)
{
	char const	*name = (char *)((uintptr_t)mach->strtab + index);

	if (__readable(&(mach->object), name, int16_t) == TRUE)
		return ((char *)name);
	return ("bad string index");
}

static struct symbol	*btree_new_node(struct machobj *mach, struct nlist_64 *sym)
{
	struct symbol	*node;

	if ((node = (struct symbol *)malloc(sizeof(struct symbol))) == NULL)
		return (NULL);
	node->value = __is_64_bytes(mach->magic) ? sym->n_value : (uint32_t)sym->n_value;
	node->name = safe_get_name(mach, sym->n_un.n_strx);
	node->type = (uint32_t)sym->n_type;
	node->sectid = (uint32_t)sym->n_sect;
	node->right = NULL;
	node->left = NULL;
	return (node);
}

static struct symbol	*btree_insert(struct symbol *root, struct symbol *node)
{
	if (root == NULL)
		return (node);
	if (strcmp(root->name, node->name) > 0)
		root->left = btree_insert(root->left, node);
	else
		root->right = btree_insert(root->right, node);
	return (root);
}

int			insert_symbol(struct machobj *mach, struct nlist_64 *sym)
{
	if (sym->n_type & N_STAB)
		return (EXIT_SUCCESS);
	if (!(mach->symbols_root = btree_insert(mach->symbols_root, btree_new_node(mach, sym))))
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void			btree_free(struct symbol *root)
{
	if (root != NULL) {
		btree_free(root->right);
		btree_free(root->left);
		free(root);
	}
}
