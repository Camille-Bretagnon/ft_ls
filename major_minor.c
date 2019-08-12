/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   major_minor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 15:48:09 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/12 13:38:21 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <stdio.h>

t_dstring		*push_major(t_dstring	*to_print, t_file *file, int padding)
{
	char	*temp;
	int		i;

	to_print = push_str(to_print, " ");
	if (file->type[0] == 'b' || file->type[0] == 'c')
	{
		temp = ft_itoa(major(file->device));
		i = padding - ft_strlen(temp);
		while (--i >= 0)
			to_print = push_str(to_print, " ");
		to_print = push_str(to_print, temp);
		free(temp);
		to_print = push_str(to_print, ",");
	}
	else
	{
		while (--padding >= 0)
			to_print = push_str(to_print, " ");
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
		to_print = push_str(to_print, " ");
	to_print = push_str(to_print, temp);
	free(temp);	
	return (to_print);
}
