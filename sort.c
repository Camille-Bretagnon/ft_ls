/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:31:14 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/15 12:58:19 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./libft/libft.h"

static void		swap(t_file **array, int i, int j)
{
	t_file		*temp;

	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void		basic_sort(t_file **array, int size, char flag)
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

void		time_sort(t_file **array, int size, char flag)
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
				if ((double)(array[j]->date - array[j + 1]->date) < 0)
					swap(array, j, j + 1);
			}
		}
		else
		{
			while (++j < i)
			{
			   if ((double)(array[j]->date - array[j + 1]->date) > 0)
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
