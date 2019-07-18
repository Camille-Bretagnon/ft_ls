/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:30:50 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/18 12:35:37 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"
#include "colors.h"
#include <unistd.h>

static t_dstring	*color_fill(t_file_array *files, 
		t_dstring *buffer, unsigned int i)
{
	if (i > files->size)
		return (NULL);
	else if (files->array[i]->type[0] == 'c')
		buffer = push_str(buffer, RED);
	else if (files->array[i]->type[0] == 'b')
		buffer = push_str(buffer, GREEN);
	else if (files->array[i]->type[0] == 'd')
		buffer = push_str(buffer, BLUE);
	else if (files->array[i]->type[0] == 'l')
		buffer = push_str(buffer, YELLOW);
	else if (files->array[i]->type[0] == 's')
		buffer = push_str(buffer, PURPLE);
	else if (files->array[i]->type[0] == 'p')
		buffer = push_str(buffer, CYAN);
	else
		buffer = push_str(buffer, WHITE);
	return (buffer);
}

static t_dstring		*simple_fill(t_file_array *files, t_dstring *buffer)
{
	unsigned int	i;

	i = 0;
	while (i < files->size)
	{
		buffer = color_fill(files, buffer, i);
		buffer = push_file_name(buffer, files->array[i]->file_name);
		i++;
	}
	return (buffer);
}

void				write_buffer(t_file_array *files, char *flags)
{
	t_dstring	*buffer;

	if (ft_strchr(flags, 'l'))
	{
		write_long_buffer(files, flags);
		return ;
	}
	if (!(buffer = create_dstring(BUFFER_SIZE, "")))
		malloc_error();
	//if flag l call function fill longdisplay
	//else fill names + flags, if flag F rajouter * etc
	simple_fill(files, buffer);	
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
