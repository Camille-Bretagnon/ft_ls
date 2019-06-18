/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:31:14 by cbretagn          #+#    #+#             */
/*   Updated: 2019/06/18 18:01:33 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./libft/libft.h"

//insertion sort name

//sort timestamp (quicksort ?)

void		insertion_sort(t_file **array, int size)
{
	int	i;
	int	j;
	t_file			*temp;

	i = 0;
	while (++i < size)
	{
		temp = array[i];
		j = i;
		while (--j >= 0)
		{
			if (ft_strcmp(temp->file_name, array[j]->file_name) > 0)
				break ;
			array[j + 1] = array[j];
		}
		array[j] = temp;
	}
}
