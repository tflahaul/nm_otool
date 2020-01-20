/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thflahau <thflahau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:43:31 by thflahau          #+#    #+#             */
/*   Updated: 2020/01/20 13:38:50 by thflahau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/mman.h>

#include "../include/nm.h"
#include "../include/nm_errors.h"
#include "../include/nm_parsing_mach_o.h"
#include "../include/nm_parsing_options.h"

/* TODO:	Gestion des fichiers 32bits, fat, archives et encodage	*/
/*		en endian CIGAM.					*/
/*		Affichage.						*/
/*		Vraiment utile de gérer le 32bits si il est déprécié	*/
/*		sous macOS ?						*/
/*		Accepter plus d'un binaire				*/

int				main(int argc, char const **argv)
{
	struct s_file		file;

	memset(&file, 0, sizeof(struct s_file));
	HANDLE_GNU_ERROR(ft_parse_options(&file, argc, argv));
	HANDLE_GNU_ERROR(ft_load_file_content(&file, file.filename));
	HANDLE_GNU_ERROR(ft_parse_mach_o_file(&file));

	ft_bubble_sort_symbols(&file);
	ft_display_symbols(&file);

	munmap((void *)file.content, file.length);
	return (EXIT_SUCCESS);
}
