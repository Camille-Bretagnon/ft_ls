/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:43:57 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/16 12:14:56 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int						is_hidden(char *file)
{
	int		len;

	len = ft_strlen(file);
	while (--len > 0)
	{
		if (file[len] == '/')
		{
			if (file[len + 1] == '.')
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

static t_dstring		*push_fileinfos(t_file *file,
						t_dstring *str, t_padding *padding, char flag)
{
	char		*t;

	if (flag == 'n' && is_hidden(file->file_name))
		return (str);
	str = push_str(str, file->type, 0);
	str = push_permissions(file->perm, str);
	t = ft_itoa(file->links);
	str = push_w_padding(str, t, padding->links + 2, 1);
	str = push_w_padding(str, file->user, padding->user + 1, 0);
	str = push_w_padding(str, file->group, padding->group + 2, 0);
	if (padding->max_major != -1)
		str = push_major(str, file, padding->max_major);
	t = (not_device(file->type[0])) ? ft_itoa(file->size) : NULL;
	str = (file->type[0] != 'b' && file->type[0] != 'c') ?
		push_w_padding(str, t, padding->max_size + 2, 1)
		: push_minor(str, file, padding->max_size + 2);
	str = push_str(str, " ", 0);
	t = timetoa(file->date.tv_sec);
	str = push_str(str, t, 1);
	str = push_str(str, " ", 0);
	str = file->type[0] == 'l' ? push_file_name(str, file->file_name, 1)
		: push_file_name(str, file->file_name, 0);
	if (file->type[0] == 'l')
		str = push_slink(str, file->file_name);
	return (str);
}

static t_dstring		*short_display(t_file *path, t_dstring *to_print)
{
	if (path->invalid == 1)
		inv_error(path->file_name);
	else if (path->type[0] != 'd')
	{
		if (path->type[0] == 'l')
		{
			to_print = push_file_name(to_print, path->file_name, 1);
			to_print = push_slink(to_print, path->file_name);
		}
		else
			to_print = push_file_name(to_print, path->file_name, 0);
	}
	return (to_print);
}

void					write_paths_infos(t_file **paths,
						char *flags, t_padding *padding)
{
	t_dstring			*to_print;
	int					i;

	i = -1;
	to_print = create_dstring(BUFFER_SIZE, "");
	if (ft_strchr(flags, 'l'))
	{
		while (paths[++i])
		{
			if (paths[i]->invalid == 1)
				inv_error(paths[i]->file_name);
			else
			{
				if (paths[i]->type[0] != 'd')
					to_print = push_fileinfos(paths[i], to_print, padding, 'a');
			}
		}
	}
	else
	{
		while (paths[++i])
			to_print = short_display(paths[i], to_print);
	}
	if (to_print->size != 0)
		write(1, to_print->str, to_print->size - 1);
	delete_dstring(to_print);
}

void					write_long_buffer(t_file_array *files, char *flags)
{
	unsigned int		i;
	t_dstring			*to_print;
	t_padding			*padding;
	char				flag;

	flag = ft_strchr(flags, 'a') ? 'a' : 'n';
	padding = init_padding();
	to_print = create_dstring(BUFFER_SIZE, "");
	if (ft_strchr(flags, 'u'))
		files = fill_stats(files, T_LASTACCESS, flag, padding);
	else
		files = fill_stats(files, T_MODIFIED, flag, padding);
	to_print = push_total(to_print, padding->nb_blocks);
	sort_files(files->array, files->size, flags);
	i = 0;
	while (i < files->size)
	{
		if (files->array[i]->invalid == 0)
			to_print = push_fileinfos(files->array[i], to_print, padding, flag);
		i++;
	}
	if (to_print->size != 0)
		write(1, to_print->str, to_print->size - 1);
	delete_padding(padding);
	delete_dstring(to_print);
}
