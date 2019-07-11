/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:00:58 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/11 16:14:16 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_H
# define DYNAMIC_H

# define BASE_CAP 	256
# define BASE_ARRAY	20
# define BUFFER_SIZE 4096

#include "ft_ls.h"

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

typedef struct		s_file_array
{
	unsigned int 	size;
	unsigned int	capacity;
	struct s_file	**array;
}					t_file_array;

typedef struct		s_array_str
{
	unsigned int	size;
	unsigned int	capacity;
	char			**array;
}					t_array_str;

typedef struct		s_padding
{
	unsigned int	links;
	unsigned int	user;
	unsigned int	group;
	unsigned long	nb_blocks;
	unsigned int	max_size;
}					t_padding;

t_dstring			*create_dstring(unsigned int cap, char *str);
t_dstring			*push_str(t_dstring *dest, char *src);
t_dstring			*push_w_padding(t_dstring *dest, char *src, unsigned int size);
void				delete_dstring(t_dstring *del);

t_darray			*create_darray(unsigned int cap);
void				delete_darray(t_darray *del);
int					cpy_darray(t_darray *dest, t_darray *src);
t_darray			*push_dstr(t_darray *dest, t_dstring *src);

t_file_array		*create_file_array(unsigned int cap);
void				delete_file_array(t_file_array *del);
int					cpy_file_array(t_file_array *dest, t_file_array *src);
t_file_array		*push_file(t_file_array *dest, struct s_file *src);

t_array_str			*create_array_str(unsigned int cap);
void				delete_array_str(t_array_str *del);
int					cpy_array_str(t_array_str *dest, t_array_str *src);
t_array_str			*push_str_on_array(t_array_str *dest, char *src);

void				print_file_array(t_file_array *files);
void				print_array_str(t_array_str *directories);

void				write_buffer(t_file_array *files, char *flags, char recursion);
void				write_long_buffer(t_file_array *files, char *flags, char recursion);

t_file_array		*fill_stats(t_file_array *files, char flag, t_padding *padding);
t_padding			*init_padding(void);

struct s_file		*fill_file_stats(struct s_file *file, char flag, t_padding *padding);
#endif
