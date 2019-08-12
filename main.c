/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:12:02 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/12 13:38:18 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char			*flags;
	char			hidden;
	t_file			**paths;
	int				i;
	int				j;
	t_padding		*padding;

	if (!(padding = init_padding()))
		malloc_error();
	flags = ft_strnew(MAX_FLAGS);
	i = get_flags(argv, flags);
	paths = get_paths(argv, argc, i);
	hidden = ft_strchr(flags, 'a') ? 'a' : 'n';
	j = -1;
	while (paths[++j])
	{
		paths[j] = ft_strchr(flags, 'u') ? fill_file_stats(paths[j], T_LASTACCESS, hidden, padding)
			: fill_file_stats(paths[j], T_MODIFIED, hidden, padding);
	}
	if (j == 1 && paths[0]->file_name[0] == '.')
	{
		open_directory(paths[0]->file_name, flags);
	}
	else
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
	write(1, "\n", 1);
	delete_simple_file_struct_array(paths);
	ft_strdel(&flags);
	free(padding);
	padding = NULL;
}
