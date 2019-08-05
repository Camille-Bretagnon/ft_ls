/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:31:14 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/05 14:49:21 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		swap(t_file **array, int i, int j)
{
	t_file		*temp;

	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

static void		basic_sort(t_file **array, int size, char flag)
{
	int	i;
	int	j;

	i = 0;
	while (++i < size)
	{
		j = i + 1;
		if (flag != 'r')
		{
			while (--j > 0 && (ft_strcmp(array[j]->file_name, array[j - 1]->file_name) < 0))
				swap(array, j, j - 1);
		}
		else
		{
			while (--j > 0 && (ft_strcmp(array[j]->file_name, array[j - 1]->file_name)) > 0)
				swap(array, j, j - 1);
		}
	}
}

static void		time_sort(t_file **array, int size, char flag)
{
	int	i;
	int	j;

	i = size;
	while (--i > 1)
	{
		j = -1;
		if (flag != 'r')
		{
			while (++j < i)
			{
				if ((array[j]->date.tv_nsec - array[j + 1]->date.tv_nsec) < 0)
					swap(array, j, j + 1);
			}
		}
		else
		{
			while (++j < i)
			{
			   if ((array[j]->date.tv_nsec - array[j + 1]->date.tv_nsec) > 0)
					swap(array, j, j + 1);
			 }
		}
	}
}

void		sort_files(t_file **array, int size, char *flags)
{
	if (ft_strchr(flags, 't'))
	{
		if (ft_strchr(flags, 'r'))
			time_sort(array, size, 'r');
		else
			time_sort(array, size, 'n');
	}
	else
	{
		if (ft_strchr(flags, 'r'))
			basic_sort(array, size, 'r');
		else
			basic_sort(array, size, 'n');
	}
}
