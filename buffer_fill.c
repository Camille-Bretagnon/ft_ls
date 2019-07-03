/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:30:50 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/03 14:40:35 by cbretagn         ###   ########.fr       */
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
	else if (files->array[i]->type == 'c')
		buffer = push_str(buffer, RED);
	else if (files->array[i]->type == 'b')
		buffer = push_str(buffer, GREEN);
	else if (files->array[i]->type == 'd')
		buffer = push_str(buffer, BLUE);
	else if (files->array[i]->type == 'l')
		buffer = push_str(buffer, YELLOW);
	else if (files->array[i]->type == 's')
		buffer = push_str(buffer, PURPLE);
	else if (files->array[i]->type == 'p')
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
		buffer = push_str(buffer, files->array[i]->file_name);
		buffer = push_str(buffer, "\n");
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
	if (!(buffer = create_dstring(2000, "")))
		return ;
	//if flag l call function fill longdisplay
	//else fill names + flags, if flag F rajouter * etc
	simple_fill(files, buffer);	
	write(1, buffer->str, buffer->size - 1);
}
