/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:00:58 by cbretagn          #+#    #+#             */
/*   Updated: 2019/05/20 17:08:28 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_H
# define DYNAMIC_H

# define BASE_CAP 	256
# define BASE_ARRAY	20

typedef struct		s_dstring
{
	unsigned int	size;
	unsigned int	capacity;
	char			*str;
}					t_dstring;

typedef struct		s_darray
{
	unsigned int	size;
	unsigned int	capacity;
	t_dstring		**array;
}					t_darray;

t_dstring			*create_dstring(unsigned int cap, char *str);
t_dstring			*push_str(t_dstring *dest, char *src);
void				delete_dstring(t_dstring *del);

t_darray			*create_darray(unsigned int cap);
void				delete_darray(t_darray *del);
int					cpy_darray(t_darray *dest, t_darray *src);
t_darray			*push_dstr(t_darray *dest, t_dstring *src);
#endif
