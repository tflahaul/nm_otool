/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:31 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/14 14:57:24 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/mman.h>

#include "include/nm.h"
#include "include/nm_symlist.h"
#include "include/nm_parsing.h"
#include "include/nm_errors.h"
#include "include/nm_parsing_options.h"

/* TODO:	Gestion des fichiers 32bits, fat, archives et encodage	*/
/*		en endian CIGAM.					*/
/*		Trier la liste (avec toutes les options)		*/
/*		Affichage.						*/
/*		Vraiment utile de gérer le 32bits si il est déprécié	*/
/*		sous macOS ?						*/
int				main(int argc, char const **argv)
{
	struct s_file		file;
	struct s_symlist	list;

	ft_list_init_head(&(list.list));
	HANDLE_GNU_ERROR(ft_parse_options(&file, argc, argv));
	HANDLE_GNU_ERROR(ft_load_file_content(&file, file.filename));
	HANDLE_GNU_ERROR(ft_parse_mach_o_file(&list, &file));

	ft_bubble_sort_list(&file, &list);
	ft_display_symbols(&file, &list);

	ft_free_list(&(list.list));
	munmap((void *)file.content, file.length);
	return (0);
}
