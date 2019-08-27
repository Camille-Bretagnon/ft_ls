/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stats.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:45:39 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/16 14:53:49 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void					fill_type(t_file *to_fill, mode_t mode)
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

static int				fun_m(t_file *file)
{
	if (file->type[0] == 'b' || file->type[0] == 'c')
		return (nb_len(major(file->device)));
	return (-1);
}

static t_file			*half_fill(t_file *file, struct stat b)
{
	file->perm = b.st_mode;
	file->links = b.st_nlink;
	file->uid = b.st_uid;
	file->gid = b.st_gid;
	file->device = b.st_rdev;
	return (file);
}

t_file					*fill_file_stats(t_file *file, char flag,
						char hidden, t_padding *p)
{
	struct stat			b;

	if (lstat(file->file_name, &b) == -1)
	{
		file->invalid = 1;
		return (file);
	}
	fill_type(file, b.st_mode);
	if (hidden == 'a' || !(is_hidden(file->file_name)))
		p->nb_blocks += b.st_blocks;
	p->links = p->links < nb_len(b.st_nlink) ? nb_len(b.st_nlink) : p->links;
	p->max_size = p->max_size < nb_len(b.st_size) ?
		nb_len(b.st_size) : p->max_size;
	p->max_size = p->max_size < nb_len(minor(b.st_rdev)) ?
		nb_len(minor(b.st_rdev)) : p->max_size;
	file = half_fill(file, b);
	p->max_major = fun_m(file) > p->max_major ? fun_m(file) : p->max_major;
	file->date = flag == 0 ? b.st_mtimespec : b.st_atimespec;
	file->size = b.st_size;
	file->user = get_username(file->uid);
	file->group = get_groupname(file->gid);
	p->user = p->user < ft_strlen(file->user) ? ft_strlen(file->user) : p->user;
	p->group = p->group < ft_strlen(file->group) ?
		ft_strlen(file->group) : p->group;
	return (file);
}

t_file_array			*fill_stats(t_file_array *files, char flag,
						char hidden, t_padding *padding)
{
	unsigned int	i;

	i = 0;
	while (i < files->size)
	{
		files->array[i] = fill_file_stats(files->array[i], flag,
					hidden, padding);
		i++;
	}
	return (files);
}
