/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:31:14 by cbretagn          #+#    #+#             */
/*   Updated: 2019/06/19 13:43:38 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./libft/libft.h"

//insertion sort name

//sort timestamp (quicksort ?)

static void		swap(t_file **array, int i, int j)
{
	t_file		*temp;

	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void			basic_sort(t_file **array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (++i < size)
	{
		j = i + 1;
		while (--j > 0 && (ft_strcmp(array[j]->file_name, array[j - 1]->file_name) < 0))
			swap(array, j, j - 1);
	}
}
