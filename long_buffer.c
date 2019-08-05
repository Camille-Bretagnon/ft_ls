/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:43:57 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/05 14:35:50 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					is_hidden(char *file)
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
		t_dstring *to_print, t_padding *padding, char flag)
{
	char		*temp;

	if (flag == 'n' && is_hidden(file->file_name))
		return (to_print);
	to_print = push_str(to_print, file->type);
	to_print = push_permissions(file->perm, to_print);
	temp = ft_itoa(file->links);
	to_print = push_w_padding(to_print, temp, padding->links + 2);
	ft_strdel(&temp);
	to_print = push_w_padding(to_print, file->user, padding->user + 1);
	to_print = push_w_padding(to_print, file->group, padding->group + 2);
	temp = ft_itoa(file->size);
	to_print = push_w_padding(to_print, temp, padding->max_size + 2);
	ft_strdel(&temp);
	to_print = push_str(to_print, " ");
	temp = timetoa(file->date);
	to_print = push_str(to_print, temp);
	ft_strdel(&temp);
	to_print = push_str(to_print, " ");
	to_print = push_file_name(to_print, file->file_name);
	if (file->type[0] == 'l')
		to_print = push_slink(to_print, file->file_name);
	return (to_print);
}

void					write_paths_infos(t_file **paths, char *flags)
{
	t_dstring			*to_print;
	t_padding			*padding;
	int					i;
	int					only_dir;
	char				flag;

	i = -1;
	only_dir = 0;
	if (!(padding = init_padding()))
		malloc_error();
	if (!(to_print = create_dstring(BUFFER_SIZE, "")))
		malloc_error();
	flag = ft_strchr(flags, 'a') ? 'a' : 'n';
	while (paths[++i] && ft_strchr(flags, 'l'))
	{
		if (paths[i]->type[0] != 'd')
		{
			only_dir++;
			paths[i] = ft_strchr(flags, 'u') ? 
				fill_file_stats(paths[i], T_LASTACCESS, flag, padding) :
				fill_file_stats(paths[i], T_MODIFIED, flag, padding);
		}
	}
	if (only_dir == 0)
		return ;
	i = -1;
	if (ft_strchr(flags, 'l'))
	{
		while (paths[++i])
		{
		if (paths[i]->type[0] != 'd')
			to_print = push_fileinfos(paths[i], to_print, padding, flag);
		}
	}
	else
	{
		while (paths[++i])
		{
			if (paths[i]->type[0] != 'd')
			{
				to_print = push_str(to_print, paths[i]->file_name);
				to_print = push_str(to_print, "\n");
			}
		}
	}
	if (to_print->size != 0)
		write(1, to_print->str, to_print->size - 1);
	write(1, "\n", 1);
	free(padding);
	padding = NULL;
	delete_dstring(to_print);
}

void					write_long_buffer(t_file_array *files, char *flags)
{
	unsigned int		i;
	t_dstring			*to_print;
	t_padding			*padding;
	char				flag;

	flag = ft_strchr(flags, 'a') ? 'a' : 'n';
	if (!(padding = init_padding()))
		malloc_error();
	if (!(to_print = create_dstring(BUFFER_SIZE, "")))
		malloc_error();
	if (ft_strchr(flags, 'u'))
		files = fill_stats(files, T_LASTACCESS, flag, padding);
	else
		files = fill_stats(files, T_MODIFIED, flag, padding);
	to_print = push_total(to_print, padding->nb_blocks);
	sort_files(files->array, files->size, flags);
	i = 0;
	while (i < files->size)
	{
		to_print = push_fileinfos(files->array[i], to_print, padding, flag);
		i++;
	}
	if (to_print->size != 0)
		write(1, to_print->str, to_print->size - 1);
	free(padding);
	padding = NULL;
	delete_dstring(to_print);
}
