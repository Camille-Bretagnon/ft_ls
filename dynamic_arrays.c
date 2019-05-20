/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_arrays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 15:12:35 by cbretagn          #+#    #+#             */
/*   Updated: 2019/05/20 17:07:24 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdlib.h>
#include "dynamic.h"

t_darray				*create_darray(unsigned int cap)
{
	t_darray	*ret;
	int			i;

	if (!(ret = (t_darray *)malloc(sizeof(t_darray))))
		return (NULL);
	ret->size = 0;
	ret->capacity = cap;
	if (!(ret->array = (t_dstring **)malloc(sizeof(t_dstring *) * cap)))
		return (NULL);
	i = -1;
	while (++i < cap)
		ret->array[i] = NULL;
	return (ret);
}

void					delete_darray(t_darray *del)
{
	int		i;

	i = -1;
	while (++i < del->size)
		delete_dstring(del->array[i]);
	free(del->array);
	del->array = NULL;
	free(del);
	del = NULL;
}

int						cpy_darray(t_darray *dest, t_darray *src)
{
	int				i;

	if (dest->capacity < src->capacity)
		return (0);
	i = -1;
	print_darray(src);
	print_darray(dest);
	while (++i < src->size)
	{
		if (!(dest->array[i] = 
					create_dstring(src->array[i]->capacity, src->array[i]->str)))
			return (-1);
	}
	dest->size = i;
	return (1);
}

t_darray				*push_dstr(t_darray *dest, t_dstring *src)
{
	t_darray	*temp;

	if (dest->capacity - dest->size > 0)
	{
		dest->array[dest->size] = src;
		dest->size += 1;
		return (dest);
	}
	temp = dest;
	dest = create_darray(temp->capacity * 2);
	if (!(cpy_darray(dest, temp)))
		return (NULL);
	dest->array[dest->size] = src;
	dest->size += 1;
	delete_darray(temp);
	return (dest);
}
