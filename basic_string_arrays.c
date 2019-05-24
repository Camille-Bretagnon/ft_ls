/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_strs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 13:34:07 by cbretagn          #+#    #+#             */
/*   Updated: 2019/05/24 15:50:40 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "dynamic.h"
#include <stdlib.h>
#include "ft_ls.h"

t_array_str	*create_array_str(unsigned int cap)
{
	t_array_str		*ret;
	unsigned int	i;

	i = 0;
	if (!(ret = (t_array_str *)malloc(sizeof(t_array_str))))
		return (NULL);
	ret->size = 0;
	ret->capacity = cap;
	if (!(ret->array = (char **)malloc(sizeof(char *) * cap)))
		return (NULL);
	while (i < cap)
		ret->array[i++] = NULL;
	return (ret);
}

void			delete_array_str(t_array_str *del)
{
	unsigned int	i;

	i = 0;
	while (i < del->size)
		ft_strdel(&del->array[i++]);
	free(del->array);
	del->array = NULL;
	free(del);
	del = NULL;
}

int				cpy_array_str(t_array_str *dest, t_array_str *src)
{
	unsigned int	i;

	if (dest->capacity < src->capacity)
		return (0);
	i = 0;
	while (i < src->size)
	{
		if (!(dest->array[i] = ft_strdup(src->array[i])))
			return (-1);
		i++;
	}
	dest->size = i;
	return (1);
}

t_array_str		*push_str_on_array(t_array_str *dest, char *src)
{
	t_array_str	*temp;

	if (dest->capacity - dest->size > 0)
	{
		dest->array[dest->size] = src;
		dest->size += 1;
		return (dest);
	}
	temp = dest;
	dest = create_array_str(temp->capacity * 2);
	if (!(cpy_array_str(dest, temp)))
		return (NULL);
	dest->array[dest->size] = src;
	dest->size += 1;
	delete_array_str(temp);
	return (dest);
}
