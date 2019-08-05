/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_on_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 14:56:59 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/05 12:03:41 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dstring			*push_file_name(t_dstring *dest, char *file)
{
	int		len;
	char	*brk;

	brk = file;
	len = ft_strlen(file);
	while (--len >= 0)
	{
		if (file[len] == '/')
		{
			brk = file + len + 1;
			break;
		}
	}
	dest = push_str(dest, brk);
	dest = push_str(dest, "\n");
	return (dest);
}

t_dstring			*push_total(t_dstring *dest, blkcnt_t total)
{
	char	*temp;

	temp = ft_itoa(total);
	dest = push_str(dest, "total ");
	dest = push_str(dest, temp);
	dest = push_str(dest, "\n");
	ft_strdel(&temp);
	return (dest);
}

t_dstring			*push_permissions(mode_t mode, t_dstring *to_print)
{
	const char	perm[10] = "rwxrwxrwx";
	char		*buffer;
	int			i;

	if (!(buffer = ft_strnew(9)))
		malloc_error();
	i = -1;
	while (++i < 9)
		buffer[i] = (mode & (1 << (8 - i))) ? perm[i] : '-';
	to_print = push_str(to_print, buffer);
	free(buffer);
	buffer = NULL;
	return (to_print);
}

//RAJOUTER spec pour time < 6 mois TODO
char					*timetoa(time_t date)
{
	char		*buffer;
	char		*ret;
	int			i;

	i = -1;
	if (!(ret = (char *)malloc(sizeof(char) * 13)))
		malloc_error();
	buffer = ctime(&date);
	while (++i < 3)
		*(ret + i) = *(buffer + 4 + i);
	*(ret + i) = ' ';
	while (++i < 6)
		*(ret + i) = *(buffer + 4 + i);
	*(ret + i) = ' ';
	while (++i < 12)
		*(ret + i) = *(buffer + 4 + i);
	*(ret + i) = '\0';
	return (ret);
}

t_dstring				*push_slink(t_dstring *to_print, char *file)
{
	char		*buffer;

	if (!(buffer = ft_strnew(256)))
		malloc_error();
	readlink(file, buffer, 256);
	to_print = push_str(to_print, " -> ");
	to_print = push_str(to_print, buffer);
	to_print = push_str(to_print, "\n");
	ft_strdel(&buffer);
	return (to_print);
}
