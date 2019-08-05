/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 14:00:58 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/05 12:32:20 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMIC_H
# define DYNAMIC_H

# define BASE_CAP 	256
# define BASE_ARRAY	256
# define BUFFER_SIZE 4096

#include "ft_ls.h"

typedef struct		s_dstring
{
	unsigned int	size;
	unsigned int	capacity;
	char			*str;
}					t_dstring;

typedef struct		s_file_array
{
	unsigned int 	size;
	unsigned int	capacity;
	struct s_file	**array;
}					t_file_array;

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

t_file_array		*create_file_array(unsigned int cap);
void				delete_file_array(t_file_array *del);
int					cpy_file_array(t_file_array *dest, t_file_array *src);
t_file_array		*push_file(t_file_array *dest, struct s_file *src);

void				write_buffer(t_file_array *files, char *flags);
void				write_long_buffer(t_file_array *files, char *flags);
t_file_array		*fill_stats(t_file_array *files, char flag, char hidden, t_padding *padding);
t_padding			*init_padding(void);
struct s_file		*fill_file_stats(struct s_file *file, char flag, char hidden, t_padding *padding);
t_dstring			*push_permissions(mode_t mode, t_dstring *to_print);
t_dstring			*push_total(t_dstring *dest, blkcnt_t total);
t_dstring			*push_file_name(t_dstring *dest, char *file);
t_dstring			*push_slink(t_dstring *dest, char *file);

#endif
