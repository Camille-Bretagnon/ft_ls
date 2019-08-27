/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_string_arrays.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:03:21 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/27 11:54:56 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dynamic.h"

t_dstring			*create_dstring(unsigned int cap, char *str)
{
	t_dstring		*ret;
	unsigned int	len;

	if (!(ret = (t_dstring *)malloc(sizeof(t_dstring))))
		malloc_error();
	len = ft_strlen(str);
	ret->capacity = cap;
	ret->size = len;
	if (!(ret->str = ft_strnew(ret->capacity)))
		malloc_error();
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

t_dstring			*push_str(t_dstring *dest, char *src, char fr)
{
	t_dstring		*temp;
	int				new_cap;
	unsigned int	len;

	len = ft_strlen(src);
	temp = dest;
	if (len < temp->capacity - temp->size)
		ft_strcpy((temp->str + temp->size), src);
	else
	{
		temp = NULL;
		new_cap = dest->capacity;
		while (len >= new_cap - dest->size)
			new_cap *= 2;
		if (!(temp = create_dstring(new_cap, dest->str)))
			malloc_error();
		delete_dstring(dest);
		ft_strcpy((temp->str + temp->size), src);
	}
	temp->size += len;
	if (fr == 1)
		ft_strdel(&src);
	return (temp);
}
