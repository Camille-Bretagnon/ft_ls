/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:12:02 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/27 11:55:10 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

static char			h(char *flags)
{
	if (ft_strchr(flags, 'a'))
		return ('a');
	return ('n');
}

static void			handle_dir(t_file **paths, int j,
					char *flags, t_padding *padding)
{
	sort_files(paths, j, flags);
	write_paths_infos(paths, flags, padding, -1);
	j = -1;
	while (paths[++j])
	{
		if (paths[j]->type[0] == 'd')
		{
			write(1, "\n", 1);
			break ;
		}
	}
	while (paths[j])
	{
		if (paths[j]->type[0] == 'd')
		{
			ft_putstr(paths[j]->file_name);
			write(1, ":\n", 2);
			open_directory(paths[j]->file_name, flags);
		}
		j++;
	}
}

static t_file		**handle_symlink(t_file **paths, char *flags,
						t_padding *padding)
{
	int				i;
	char			date;
	char			*file;

	if (ft_strchr(flags, 'l'))
		return (paths);
	i = -1;
	if (ft_strchr(flags, 'u'))
		date = T_LASTACCESS;
	else
		date = T_MODIFIED;
	while (paths[++i])
	{
		if (paths[i]->type[0] == 'l')
		{
			if (!(file = ft_strnew(4096)))
				malloc_error();
			readlink(paths[i]->file_name, file, 4096);
			delete_file_struct(paths[i]);
			paths[i] = init_file_struct(file, 1);
			add_slash(paths[i]->file_name);
			paths[i] = fill_file_stats(paths[i], date, 'a', padding);
		}
	}
	return (paths);
}

int					main(int argc, char **argv)
{
	char			*flags;
	t_file			**paths;
	int				i;
	t_padding		*padding;

	if (!(padding = init_padding()))
		malloc_error();
	flags = ft_strnew(MAX_FLAGS);
	i = get_flags(argv, flags);
	paths = get_paths(argv, argc, i);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strchr(flags, 'u') ? fill_file_stats(paths[i],
				T_LASTACCESS, h(flags), padding)
			: fill_file_stats(paths[i], T_MODIFIED, h(flags), padding);
	}
	paths = handle_symlink(paths, flags, padding);
	if (i == 1 && paths[0]->type[0] == 'd')
		open_directory(paths[0]->file_name, flags);
	else
		handle_dir(paths, i, flags, padding);
	delete_simple_file_struct_array(paths);
	ft_strdel(&flags);
	delete_padding(padding);
}
