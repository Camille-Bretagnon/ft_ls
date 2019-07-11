/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:12:02 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/11 15:59:54 by cbretagn         ###   ########.fr       */
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
	struct stat		buffer;

	flags = ft_strnew(MAX_FLAGS);
	i = get_flags(argv, flags);
	paths = get_paths(argv, argc, i);
	j = -1;
	while (paths[++j])
	{
		stat(paths[j]->file_name, &buffer);
		fill_struct(paths[j], buffer);
	}
	basic_sort(paths, j); //add time sort
	write_paths_infos(paths, flags);
	j = -1;
	while (paths[++j])
	{
		if (paths[j]->type[0] == 'd')
			open_directory(paths[j]->file_name, flags, 1);
	}
	delete_simple_file_struct_array(paths);
	ft_strdel(&flags);
}
