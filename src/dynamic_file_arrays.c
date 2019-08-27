/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_file_arrays.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:34:07 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/16 15:10:32 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dynamic.h"
#include "../ft_ls.h"

t_file_array	*create_file_array(unsigned int cap)
{
	t_file_array	*ret;
	unsigned int	i;

	i = 0;
	if (!(ret = (t_file_array *)malloc(sizeof(t_file_array))))
		malloc_error();
	ret->size = 0;
	ret->capacity = cap;
	if (!(ret->array = (t_file **)malloc(sizeof(t_file *) * cap)))
		malloc_error();
	while (i < cap)
		ret->array[i++] = NULL;
	return (ret);
}

void			delete_file_array(t_file_array *del)
{
	unsigned int	i;

	i = 0;
	while (i < del->size)
		delete_file_struct(del->array[i++]);
	free(del->array);
	del->array = NULL;
	free(del);
	del = NULL;
}

int				cpy_file_array(t_file_array *dest, t_file_array *src)
{
	unsigned int	i;

	if (dest->capacity < src->capacity)
		return (0);
	i = 0;
	while (i < src->size)
	{
		dest->array[i] = src->array[i];
		i++;
	}
	dest->size = i;
	return (1);
}

t_file_array	*push_file(t_file_array *dest, t_file *src)
{
	t_file_array	*temp;

	if (dest->capacity - dest->size > 0)
	{
		dest->array[dest->size] = src;
		dest->size += 1;
		return (dest);
	}
	temp = dest;
	dest = create_file_array(temp->capacity * 2);
	if (!(cpy_file_array(dest, temp)))
	{
		delete_file_array(dest);
		return (NULL);
	}
	dest->array[dest->size] = src;
	dest->size += 1;
	free(temp->array);
	temp->array = NULL;
	free(temp);
	temp = NULL;
	return (dest);
}
