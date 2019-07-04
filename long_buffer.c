/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:43:57 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/04 19:11:42 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

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

static t_dstring		*push_permissions(mode_t mode, t_dstring *to_print)
{
	const char	perm[9] = "rwxrwxrwx";
	char		*buffer;
	int			i;

	if (!(buffer = ft_strnew(8)))
		exit(0); //perror
	i = -1;
	while (++i < 9)
		buffer[i] = (mode & (1 << (8 - i))) ? perm[i] : '-';
	to_print = push_str(to_print, buffer);
	free(buffer);
	buffer = NULL;
	return (to_print);
}

#include <stdio.h>

static t_dstring		*push_time(char *buffer, t_dstring *to_print)
{
	//time_t		now;
	//char		*buffer;
	char		*to_push;
	int			i;

	i = -1;
	to_push = ft_strnew(12);
		//exit(0); //perror
	//time(&now);
	while (++i < 3)
		to_push[i] = buffer[4 + i];
	to_push[i] = ' ';
	while (++i < 6)
		to_push[i] = buffer[4 + i];
	to_push[i] = ' ';
	while (++i < 12)
		to_push[i] = buffer[4 + i];
	to_print = push_str(to_print, to_push);
	free(to_push);
	to_push = NULL;
	return (to_print);
}
	
static t_dstring		*push_fileinfos(t_file *file, t_dstring *to_print, t_padding *padding)
{
	to_print = push_str(to_print, file->type);
	to_print = push_permissions(file->perm, to_print);
	to_print = push_str(to_print, " ");
	to_print = push_w_padding(to_print, ft_itoa(file->links), padding->links);
	to_print = push_str(to_print, " ");
	to_print = push_w_padding(to_print, file->user, padding->user);
	to_print = push_str(to_print, " ");
	to_print = push_w_padding(to_print, file->group, padding->group);
	to_print = push_str(to_print, " ");
	to_print = push_str(to_print, " ");
	to_print = push_w_padding(to_print, ft_itoa(file->size), padding->max_size);
	to_print = push_str(to_print, " ");
	to_print = push_time(ft_strdup(ctime(&file->date)), to_print);
	to_print = push_str(to_print, " ");
	to_print = push_str(to_print, file->file_name);
	to_print = push_str(to_print, "\n");
	return (to_print);
}

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
	i = 0;
	while (i < files->size)
	{
		to_print = push_fileinfos(files->array[i], to_print, padding);
		i++;
	}
	write(1, to_print->str, to_print->size - 1);
}
