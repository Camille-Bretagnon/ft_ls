/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 13:43:57 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/01 14:21:13 by cbretagn         ###   ########.fr       */
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

static t_dstring		*push_username(t_dstring *dest, uid_t uid)
{
	struct passwd		*get_names;

	get_names = getpwuid(uid);
	dest = push_w_padding(dest, get_names->pw_name, USER);
	return (dest);
}

static t_dstring		*push_groupname(t_dstring *dest, gid_t gid)
{
	struct group		*get_names;

	get_names = getgrgid(gid);
	dest = push_w_padding(dest, get_names->gr_name, GROUP);
	return (dest);
}

#include <stdio.h>

void					write_long_buffer(t_file_array *files, char *flags)
{
	unsigned int		nb_blocks;
	unsigned int		i;
	struct stat			buffer;
	t_dstring			*to_print;

	(void)flags;
	if (!(to_print = create_dstring(BUFFER_SIZE, "")))
		return ;
	i = 0;
	nb_blocks = 0;
	while (i < files->size)
	{
		stat(files->array[i]->file_name, &buffer);
		nb_blocks += buffer.st_blocks;
		//push perm
		to_print = push_w_padding(to_print, ft_itoa(buffer.st_nlink), LINKS);
		to_print = push_username(to_print, buffer.st_uid);
		to_print = push_groupname(to_print, buffer.st_gid);
		//specific fun blocks
		//specific fun time
		to_print = push_str(to_print, files->array[i]->file_name);
		to_print = push_str(to_print, "\n");
		i++;
	}
	write(1, to_print->str, to_print->size - 1);
}
