/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:01:38 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/04 17:15:15 by cbretagn         ###   ########.fr       */
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
			if (!(ft_strchr("larRtFdiuhn", argv[ret][j]))) //verif les options
				write(1, "ls: illegal options\nusage: ls [verfi options] [file ...]", 56); //ajouter un return -1, recuperer l'erreur free etc
			if (!(ft_strchr(flags, argv[ret][j])))
				flags[++i] = argv[ret][j];
		}
		ret++;
	}
	return (ret);
}

t_file		*init_file_struct(char *name) //TODO rajouter long display dans malloc, prend en 
											// param flags, car rajout uniquement si l 
											// rajouter gestion flags inexistants ex K
{
	t_file	*ret;

	if (!(ret = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	if (!(ret->type = ft_strnew(1)))
		return (NULL);
	if (!(ret->file_name = ft_strdup(name)))
		return (NULL);
	ret->user = NULL;
	ret->group = NULL;
	return (ret);
}

void		delete_file_struct(t_file *del)
{
	free(del->type);
	del->type = NULL;
	free(del->file_name);
	del->file_name = NULL;
	if (del->user)
	{
		free(del->user);
		del->user = NULL;
	}
	if (del->group)
	{
		free(del->group);
		del->group = NULL;
	}
	free(del);
	del = NULL;
}

t_file		**get_paths(char **argv, int argc, int i)
{
	t_file			**ret;
	int				nb_path;
	int				j;

	j = -1;
	nb_path = argc - i == 0 ? 1 : argc - i;
	if (!(ret = (t_file **)malloc(sizeof(t_file *) * (nb_path + 1))))
			return (NULL);
	if (argc - i == 0)
		ret[++j] = init_file_struct(".");
	while (++j < nb_path)
	{
		if (!(ret[j] = init_file_struct(argv[i++])))
			return (NULL);
	}
	ret[j] = NULL;
	return (ret);
}
