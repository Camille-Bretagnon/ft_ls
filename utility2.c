/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 15:09:50 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/12 16:12:40 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		usage(void)
{
	write(1, "ls: illegal options\n usage: ls [larRtFnpTu] [file ...]\n", 54);
	exit(-1);
}

int			not_device(char c)
{
	return (c != 'b' && c != 'c');
}
