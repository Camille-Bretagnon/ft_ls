/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:01:38 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/16 10:36:12 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"
#include <stdlib.h>
#include <unistd.h>

int			get_flags(char **argv, char *flags)
{
	int		ret;
	int		i;
	int		j;

	ret = 1;
	i = -1;
	while (argv[ret] && argv[ret][0] == '-')
	{
		if (argv[ret][1] == '\0')
			return (ret);
		if (argv[ret][1] == '-')
			return (ret + 1);
		j = 0;
		while (argv[ret][++j])
		{
			if (!(ft_strchr("larRtFnpTu", argv[ret][j])))
				usage();
			if (!(ft_strchr(flags, argv[ret][j])))
				flags[++i] = argv[ret][j];
		}
		ret++;
	}
	return (ret);
}

t_file		*init_file_struct(char *name, char free)
{
	t_file	*ret;

	if (!(ret = (t_file *)malloc(sizeof(t_file))))
		malloc_error();
	if (!(ret->type = ft_strnew(1)))
		malloc_error();
	if (free == 1)
		ret->file_name = name;
	else
	{
		if (!(ret->file_name = ft_strdup(name)))
			malloc_error();
	}
	ret->invalid = 0;
	ret->user = NULL;
	ret->group = NULL;
	return (ret);
}

void		delete_file_struct(t_file *del)
{
	ft_strdel(&del->type);
	ft_strdel(&del->file_name);
	if (del->user)
		ft_strdel(&del->user);
	if (del->group)
		ft_strdel(&del->group);
	free(del);
	del = NULL;
}

void		delete_simple_file_struct_array(t_file **to_del)
{
	int		i;

	i = -1;
	while (to_del[++i])
		delete_file_struct(to_del[i]);
	free(to_del);
	to_del = NULL;
}

t_file		**get_paths(char **argv, int argc, int i)
{
	t_file			**ret;
	int				nb_path;
	int				j;

	j = -1;
	nb_path = argc - i == 0 ? 1 : argc - i;
	if (!(ret = (t_file **)malloc(sizeof(t_file *) * (nb_path + 1))))
		malloc_error();
	if (argc - i == 0)
	{
		if (!(ret[++j] = init_file_struct(".", 0)))
			malloc_error();
	}
	while (++j < nb_path)
	{
		if (!(ret[j] = init_file_struct(argv[i++], 0)))
			malloc_error();
	}
	ret[j] = NULL;
	return (ret);
}
