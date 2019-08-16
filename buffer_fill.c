/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 14:30:50 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/16 12:39:10 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"

static t_dstring			*simple_fill(t_file_array *files,
							t_dstring *buffer, char flag)
{
	unsigned int	i;

	i = 0;
	while (i < files->size)
	{
		if ((flag == 'a' || !(is_hidden(files->array[i]->file_name))) 
					&& files->array[i]->invalid == 0)
		{
			if (files->array[i]->type[0] == 'l')
			{
				buffer = push_file_name(buffer, files->array[i]->file_name, 1);
				buffer = push_slink(buffer, files->array[i]->file_name);
			}
			else
				buffer = push_file_name(buffer, files->array[i]->file_name, 0);
		}
		i++;
	}
	return (buffer);
}

static t_file_array			*fill_date(t_file_array *files, char flag)
{
	unsigned int		i;
	struct stat			buffer;

	i = 0;
	while (i < files->size)
	{
		lstat(files->array[i]->file_name, &buffer);
		files->array[i]->date = flag == 'u' ?
			buffer.st_atimespec : buffer.st_mtimespec;
		fill_type(files->array[i], buffer.st_mode);
		i++;
	}
	return (files);
}

void						write_buffer(t_file_array *files, char *flags)
{
	t_dstring	*buffer;
	char		flag;
	char		flag_time;

	flag = (ft_strchr(flags, 'a')) ? 'a' : 'n';
	if (ft_strchr(flags, 'l'))
	{
		write_long_buffer(files, flags);
		return ;
	}
	if (!(buffer = create_dstring(BUFFER_SIZE, "")))
		malloc_error();
	if (ft_strchr(flags, 't'))
	{
		flag_time = ft_strchr(flags, 'u') ? 'u' : 't';
		files = fill_date(files, flag_time);
	}
	sort_files(files->array, files->size, flags);
	simple_fill(files, buffer, flag);
	write(1, buffer->str, buffer->size - 1);
}

t_dstring					*push_w_padding(t_dstring *dest,
							char *src, unsigned int size, char fr)
{
	unsigned int		padding;
	unsigned int		i;

	padding = size - ft_strlen(src);
	i = 0;
	while (++i <= padding)
		dest = push_str(dest, " ", 0);
	dest = fr == 1 ? push_str(dest, src, 1) : push_str(dest, src, 0);
	return (dest);
}

void						print_directory(char *directory)
{
	ft_putstr(directory);
	write(1, ":\n", 2);
}
