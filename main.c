/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:12:02 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/18 16:35:49 by cbretagn         ###   ########.fr       */
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
	free(padding);
	padding = NULL;
}
