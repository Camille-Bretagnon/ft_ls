/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:12:02 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/12 14:27:50 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

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
	write_paths_infos(paths, flags, padding);
	j = -1;
	while (paths[++j])
	{
		if (paths[j]->type[0] == 'd')
		{
			ft_putstr(paths[j]->file_name);
			write(1, ":\n", 2);
			open_directory(paths[j]->file_name, flags);
			if (paths[j + 1])
				write(1, "\n\n", 2);
		}
	}
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
	if (i == 1 && paths[0]->file_name[0] == '.')
		open_directory(paths[0]->file_name, flags);
	else
		handle_dir(paths, i, flags, padding);
	write(1, "\n", 1);
	delete_simple_file_struct_array(paths);
	ft_strdel(&flags);
	delete_padding(padding);
}
