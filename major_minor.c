/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_minor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:48:09 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/12 16:04:41 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dstring		*push_major(t_dstring *to_print, t_file *file, int padding)
{
	char	*temp;
	int		i;

	to_print = push_str(to_print, " ", 0);
	if (file->type[0] == 'b' || file->type[0] == 'c')
	{
		temp = ft_itoa(major(file->device));
		i = padding - ft_strlen(temp);
		while (--i >= 0)
			to_print = push_str(to_print, " ", 0);
		to_print = push_str(to_print, temp, 1);
		to_print = push_str(to_print, ",", 0);
	}
	else
	{
		while (--padding >= 0)
			to_print = push_str(to_print, " ", 0);
	}
	return (to_print);
}

t_dstring		*push_minor(t_dstring *to_print, t_file *file, int padding)
{
	char	*temp;
	int		i;

	temp = ft_itoa(minor(file->device));
	i = padding - ft_strlen(temp);
	while (--i > 0)
		to_print = push_str(to_print, " ", 0);
	to_print = push_str(to_print, temp, 1);
	return (to_print);
}
