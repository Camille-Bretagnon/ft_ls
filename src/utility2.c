/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:09:50 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/27 11:18:50 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void					usage(void)
{
	write(1, "ls: illegal options\n usage: ls [larRtu] [file ...]\n", 51);
	exit(-1);
}

int						not_device(char c)
{
	return (c != 'b' && c != 'c');
}

void					inv_error(char *file)
{
	write(1, "ls : ", 5);
	ft_putstr(file);
	write(1, ": No such file or directory\n", 28);
}

unsigned int			nb_len(unsigned int nb)
{
	unsigned int		ret;

	ret = 0;
	while (nb != 0)
	{
		nb /= 10;
		ret++;
	}
	return (ret);
}

void					add_slash(char *file_name)
{
	char		buffer[4097];
	int			i;

	ft_strcpy(buffer, file_name);
	if (ft_strncmp("private", file_name, 7) != 0)
		return ;
	file_name[0] = '/';
	i = 0;
	while (buffer[++i])
		file_name[i] = buffer[i - 1];
	file_name[i] = buffer[i - 1];
}
