/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:30:50 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/05 14:33:59 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

static t_dstring		*simple_fill(t_file_array *files, t_dstring *buffer, char flag)
{
	unsigned int	i;

	i = 0;
	while (i < files->size)
	{
		if (flag == 'a' || !(is_hidden(files->array[i]->file_name)))
		{
			buffer = push_file_name(buffer, files->array[i]->file_name);
		}
		i++;
	}
	return (buffer);
}

void				write_buffer(t_file_array *files, char *flags)
{
	t_dstring	*buffer;
	char		flag;

	flag = (ft_strchr(flags, 'a')) ? 'a' : 'n';
	if (ft_strchr(flags, 'l'))
	{
		write_long_buffer(files, flags);
		return ;
	}
	if (!(buffer = create_dstring(BUFFER_SIZE, "")))
		malloc_error();
	//if flag l call function fill longdisplay
	//else fill names + flags, if flag F rajouter * etc
	simple_fill(files, buffer, flag);	
	write(1, buffer->str, buffer->size - 1);
}

t_dstring			*push_w_padding
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

void				print_directory(char *directory)
{
	write(1, "\n\n", 2);
	ft_putstr(directory);
	write(1, ":\n", 2);
}
