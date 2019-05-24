/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:45:39 by cbretagn          #+#    #+#             */
/*   Updated: 2019/05/24 15:21:38 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

static void		fill_type(t_file *to_fill, mode_t mode)
{
	if (mode & S_IFREG)
		to_fill->type = '-';
	else if (mode & S_IFDIR)
		to_fill->type = 'd';
	else if (mode & S_IFLNK)
		to_fill->type = 'l';
	else if (mode & S_IFIFO)
		to_fill->type = 'p';
	else if (mode & S_IFSOCK)
		to_fill->type = 's';
	else if (mode & S_IFCHR)
		to_fill->type = 'c';
	else if (mode & S_IFBLK)
		to_fill->type = 'b';
}

//ls long display
//
//perm = 10 + 1@+etc + 1 esp + 3 (nb links) + 2esp +
// 8 (user name) +  2 espa + 10 (group name) + 2 esp + taille octet (?) + 1 esp
// + mois (3) + 1 esp + jour (2) + 1 esp + date ou annee (5) + 1 esp + name (max 256)
//
void			fill_struct(t_file *to_fill, struct stat buffer)
{
	to_fill->date = buffer.st_mtime;
	fill_type(to_fill, buffer.st_mode);
}
