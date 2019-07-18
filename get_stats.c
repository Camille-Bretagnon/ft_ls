/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:45:39 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/18 13:59:40 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

static void			fill_type(t_file *to_fill, mode_t mode)
{
	if (S_ISLNK(mode))
		to_fill->type[0] = 'l';
	else if (S_ISDIR(mode))
		to_fill->type[0] = 'd';
	else if (S_ISREG(mode))
		to_fill->type[0] = '-';
	else if (S_ISFIFO(mode))
		to_fill->type[0] = 'p';
	else if (S_ISSOCK(mode))
		to_fill->type[0] = 's';
	else if (S_ISCHR(mode))
		to_fill->type[0] = 'c';
	else if (S_ISBLK(mode))
		to_fill->type[0] = 'b';
}

void			fill_struct(t_file *to_fill, struct stat buffer)
{
	to_fill->date = buffer.st_mtime;
	fill_type(to_fill, buffer.st_mode);
}

static unsigned int		nb_len(unsigned int nb)
{
	unsigned int		ret;

	ret = 0;
	while (nb != 0)
	{
		nb /= 10;
		ret++;
	}
	return (ret);
}

t_file					*fill_file_stats(t_file *file, char flag, char hidden, t_padding *padding)
{
	struct stat 		buffer;

	stat(file->file_name, &buffer);
	fill_type(file, buffer.st_mode);
	if (file->type[0] == 'l')
		lstat(file->file_name, &buffer);
	if (hidden == 'a' || !(is_hidden(file->file_name)))
		padding->nb_blocks += buffer.st_blocks;
	padding->links = padding->links < nb_len(buffer.st_nlink) ?
		nb_len(buffer.st_nlink) : padding->links;
	padding->max_size = padding->max_size < nb_len(buffer.st_size) ?
		nb_len(buffer.st_size) : padding->max_size;
	file->perm = buffer.st_mode;
	file->links = buffer.st_nlink;
	file->uid = buffer.st_uid;
	file->gid = buffer.st_gid;
	file->date = flag == 0 ? buffer.st_mtime : buffer.st_atime;
	file->size = buffer.st_size;
	file->user = get_username(file->uid);
	file->group = get_groupname(file->gid);
	padding->user = padding->user < ft_strlen(file->user) ? 
		ft_strlen(file->user) : padding->user;
	padding->group = padding->group < ft_strlen(file->group) ? 
		ft_strlen(file->group) : padding->group;
	return (file);
}

t_file_array			*fill_stats(t_file_array *files, char flag, char hidden, t_padding *padding)
{
	unsigned int	i;

	i = 0;
	while (i < files->size)
	{
		files->array[i] = fill_file_stats(files->array[i], flag, hidden, padding);
		i++;
	}
	return (files);
}
