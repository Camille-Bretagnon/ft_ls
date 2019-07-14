/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string_arrays.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:03:21 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/14 14:36:23 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdlib.h>
#include "dynamic.h"

t_dstring			*create_dstring(unsigned int cap, char *str)
{
	t_dstring		*ret;
	unsigned int	len;

	if (!(ret = (t_dstring *)malloc(sizeof(t_dstring))))
		return (NULL);
	len = ft_strlen(str);
	if (cap < len)
		return (NULL);
	ret->capacity = cap;
	ret->size = len;
	if (!(ret->str = ft_strnew(ret->capacity)))
		return (NULL);
	if (str[0] != '\0')
		ft_strcpy(ret->str, str);
	return (ret);
}

void				delete_dstring(t_dstring *del)
{
	ft_strdel(&del->str);
	free(del);
	del = NULL;
}

#include <stdio.h>

t_dstring			*push_str(t_dstring *dest, char *src)
{
	t_dstring		*temp;
	int				new_cap;
	unsigned int	len;

	len = ft_strlen(src);
	if (len < dest->capacity - dest->size)
	{
		ft_strcpy((dest->str + dest->size), src);
		dest->size += len;
		//printf("src is %s dest is %s len is %d size is %u\n", src, dest->str, len, dest->size);
	}
	else
	{
		temp = dest;
		new_cap = temp->capacity;
		while (len > new_cap - temp->size)
			new_cap *= 2;
		if (!(dest = create_dstring(new_cap, temp->str)))
			return (NULL);
		delete_dstring(temp);
		ft_strcpy((dest->str + dest->size), src);
		dest->size += len;
	}
	return (dest);
}
