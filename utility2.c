/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:09:50 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/16 13:11:07 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					usage(void)
{
	write(1, "ls: illegal options\n usage: ls [larRtFnpTu] [file ...]\n", 54);
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
	write(1, ": No such file or directory", 27);
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
