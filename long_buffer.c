/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:43:57 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/14 15:24:06 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


//static t_dstring		*push_file_name(char *filename, t_dstring *to_print)
	
static t_dstring		*push_fileinfos(t_file *file, t_dstring *to_print, t_padding *padding)
{
	char		*temp;

	to_print = push_str(to_print, file->type);
	to_print = push_permissions(file->perm, to_print);
	to_print = push_str(to_print, " ");
	temp = ft_itoa(file->links);
	to_print = push_w_padding(to_print, temp, padding->links);
	ft_strdel(&temp);
	to_print = push_str(to_print, " ");
	to_print = push_w_padding(to_print, file->user, padding->user);
	to_print = push_str(to_print, " ");
	to_print = push_w_padding(to_print, file->group, padding->group);
	to_print = push_str(to_print, " ");
	to_print = push_str(to_print, " ");
	temp = ft_itoa(file->size);
	to_print = push_w_padding(to_print, temp, padding->max_size);
	ft_strdel(&temp);
	to_print = push_str(to_print, " ");
	temp = timetoa(file->date);
	to_print = push_str(to_print, temp);
	ft_strdel(&temp);
	to_print = push_str(to_print, " ");
	to_print = push_file_name(to_print, file->file_name);
	return (to_print);
}

void					write_paths_infos(t_file **paths, char *flags)
{
	t_dstring			*to_print;
	t_padding			*padding;
	int					i;

	i = -1;
	if (!(padding = init_padding()))
		malloc_error();
	if (!(to_print = create_dstring(BUFFER_SIZE, "")))
		malloc_error();
	while (paths[++i] && ft_strchr(flags, 'l'))
	{
		if (paths[i]->type[0] != 'd')
			paths[i] = ft_strchr(flags, 'u') ? 
				fill_file_stats(paths[i], T_LASTACCESS, padding) :
				fill_file_stats(paths[i], T_MODIFIED, padding);
	}
	i = -1;
	if (ft_strchr(flags, 'l'))
	{
		while (paths[++i])
		{
		if (paths[i]->type[0] != 'd')
			to_print = push_fileinfos(paths[i], to_print, padding);//rajouter le /n
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
	free(padding);
	padding = NULL;
	delete_dstring(to_print);
}

void					write_long_buffer(t_file_array *files, char *flags, char recursion)
{
	unsigned int		i;
	t_dstring			*to_print;
	t_padding			*padding;

	(void)flags;//check if flags used, probably sent to push file infos
	if (!(padding = init_padding())) //LEAKS PADDING
		malloc_error();
	if (!(to_print = create_dstring(BUFFER_SIZE, ""))) // LEAKS DSTRING
		malloc_error();
	if (ft_strchr(flags, 'u'))
		files = fill_stats(files, T_LASTACCESS, padding);
	else
		files = fill_stats(files, T_MODIFIED, padding);
	if (recursion == 1)
		to_print = push_total(to_print, padding->nb_blocks);
	i = 0;
	while (i < files->size)
	{
		to_print = push_fileinfos(files->array[i], to_print, padding);
		i++;
	}
	if (to_print->size != 0)
		write(1, to_print->str, to_print->size - 1);
	free(padding);
	padding = NULL;
	delete_dstring(to_print);
}
