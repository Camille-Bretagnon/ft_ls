/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:45:39 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/11 13:43:00 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

static void		fill_type(t_file *to_fill, mode_t mode)
{
	if (mode & S_IFREG)
		to_fill->type[0] = '-';
	else if (mode & S_IFDIR)
		to_fill->type[0] = 'd';
	else if (mode & S_IFLNK)
		to_fill->type[0] = 'l';
	else if (mode & S_IFIFO)
		to_fill->type[0] = 'p';
	else if (mode & S_IFSOCK)
		to_fill->type[0] = 's';
	else if (mode & S_IFCHR)
		to_fill->type[0] = 'c';
	else if (mode & S_IFBLK)
		to_fill->type[0] = 'b';
}

void			fill_struct(t_file *to_fill, struct stat buffer)
{
	to_fill->date = buffer.st_mtime;
	fill_type(to_fill, buffer.st_mode);
}
