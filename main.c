/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:12:02 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/16 12:15:08 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

int		main(int argc, char **argv)
{
	char			*flags;
	t_file			**paths;
	int				i;
	int				j;
	t_padding		*padding;

	if (!(padding = init_padding()))
		malloc_error();
	flags = ft_strnew(MAX_FLAGS);
	i = get_flags(argv, flags);
	paths = get_paths(argv, argc, i);
	j = -1;
	while (paths[++j])
	{
		paths[j] = ft_strchr(flags, 'u') ? fill_file_stats(paths[j], T_LASTACCESS, padding)
			: fill_file_stats(paths[j], T_MODIFIED, padding);
	}
	sort_files(paths, j, flags);
	write_paths_infos(paths, flags);
	j = -1;
	while (paths[++j])
	{
		if (paths[j]->type[0] == 'd')
			open_directory(paths[j]->file_name, flags);
	}
	write(1, "\n", 1);
	delete_simple_file_struct_array(paths);
	ft_strdel(&flags);
}
