/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:43:57 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/03 14:46:09 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <unistd.h>

//use t_dstring && function push_str(t_dstring *, char *)
//
//var keep total blocks, write first then buffer
//
//permissions nb links user group blocks date hour colortag name {symbol if flag F} /n

static t_dstring		*push_w_padding
						(t_dstring *dest, char *src, unsigned int size)
{
	unsigned int		padding;
	unsigned int		i;

	padding = size - ft_strlen(src);
	i = 0;
	while (++i <= padding)
		dest = push_str(dest, " ");
	dest = push_str(dest, src);
	return (dest);
}

#include <stdio.h>
t_dstring				*push_fileinfos(t_file *file, t_dstring *to_print, t_padding *padding)
{
	//perm
	to_print = push_w_padding(to_print, ft_itoa(file->links), padding->links);
	to_print = push_str(to_print, " ");
	to_print = push_w_padding(to_print, file->user, padding->user);
	to_print = push_str(to_print, " ");
	to_print = push_w_padding(to_print, file->group, padding->group);
	to_print = push_str(to_print, " ");
	to_print = push_str(to_print, " ");
	//date
	to_print = push_w_padding(to_print, ft_itoa(file->size), padding->max_size);
	to_print = push_str(to_print, " ");
	to_print = push_str(to_print, file->file_name);
	to_print = push_str(to_print, "\n");
	return (to_print);
}

/*void					writefile(t_file *file)
{
	ft_putstr(ft_itoa(file->links));
	ft_putstr(" ");
	ft_putstr(file->user);
	ft_putstr(" ");
	ft_putstr(file->group);
	ft_putstr(" ");
	ft_putstr(ft_itoa(file->size));
	ft_putstr(" ");
	ft_putstr(file->file_name);
	ft_putstr("\n");
}*/

void					write_long_buffer(t_file_array *files, char *flags)
{
	unsigned int		i;
	t_dstring			*to_print;
	t_padding			*padding;

	(void)flags;
	if (!(padding = init_padding()))
		return ;//perror
	if (!(to_print = create_dstring(BUFFER_SIZE, "")))
		return ;//perror
	if (ft_strchr(flags, 'u'))
		files = fill_stats(files, T_LASTACCESS, padding);
	else
		files = fill_stats(files, T_MODIFIED, padding);
	to_print = push_str(to_print, "total ");
	to_print = push_str(to_print, ft_itoa(padding->nb_blocks));
	to_print = push_str(to_print, "\n");
	printf("max size %d\n", padding->max_size);
	i = 0;
	while (i < files->size)
	{
		to_print = push_fileinfos(files->array[i], to_print, padding);
		//writefile(files->array[i]);
		i++;
	}
	write(1, to_print->str, to_print->size - 1);
}
