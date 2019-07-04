/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:32:04 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/04 17:43:45 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "ft_ls.h"
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

static void			fill_type(t_file *to_fill, char mode)
{
	if (mode == DT_DIR)
		to_fill->type[0] = 'd';
	else if (mode == DT_FIFO)
		to_fill->type[0] = 'p';
	else if (mode == DT_SOCK)
		to_fill->type[0] = 's';
	else if (mode == DT_CHR)
		to_fill->type[0] = 'c';
	else if (to_fill->type[0] == DT_BLK)
		to_fill->type[0] = 'b';
	else if (to_fill->type[0] == DT_LNK)
		to_fill->type[0] = 'l';
	else
		to_fill->type[0] = '-';
}

static t_array_str	*push_directory(t_array_str *rec_dir, char *path, char *file)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(file) + 2))))
		return (NULL);
	ft_strcpy(str, path);
	ft_strcat(str, "/");
	ft_strcat(str, file);
	rec_dir = push_str_on_array(rec_dir, str);
	return(rec_dir);
}

static t_file_array	*read_directory(struct dirent *buffer, t_file_array *files)
{
	files = push_file(files, init_file_struct(buffer->d_name));
	fill_type(files->array[files->size - 1], buffer->d_type);
	return (files);
}

static int			print_error(void)
{
	perror("ls :");
	return (-1);
}

int					open_directory(char *directory, char *flags)
{
	DIR				*dir;
	struct dirent	*buffer;
	t_file_array	*files;
	t_array_str		*rec_dir;
	unsigned int	i;

	if (!(dir = opendir(directory)))
		return (print_error());
	if (!(files = create_file_array(BASE_ARRAY)))
		return (-1);
	rec_dir = ft_strchr(flags, 'R') ? create_array_str(BASE_ARRAY) : NULL;
	while ((buffer = readdir(dir)))
	{
		if (rec_dir != NULL && buffer->d_type == DT_DIR && buffer->d_name[0] != '.')
			rec_dir = push_directory(rec_dir, directory, buffer->d_name);
		files = read_directory(buffer, files);
	}
	//sort array file
	//fill buffer and print
	//sort array directories
	/*print_file_array(files);
	print_array_str(rec_dir);*/
	//sort(files->array, files->size, flags);
	write_buffer(files, flags);
	i = 0;
	if (rec_dir != NULL)
	{
		while (i < rec_dir->size)
			open_directory(rec_dir->array[i++], flags);
	}
	return (0);
}
