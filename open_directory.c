/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:32:04 by cbretagn          #+#    #+#             */
/*   Updated: 2019/05/24 16:02:46 by cbretagn         ###   ########.fr       */
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
		to_fill->type = 'd';
	else if (mode == DT_FIFO)
		to_fill->type = 'p';
	else if (mode == DT_SOCK)
		to_fill->type = 's';
	else if (mode == DT_CHR)
		to_fill->type = 'c';
	else if (to_fill->type == DT_BLK)
		to_fill->type = 'b';
	else if (to_fill->type == DT_LNK)
		to_fill->type = 'l';
	else
		to_fill->type = '-';
}

static int			push_directory(t_array_str *rec_dir, char *path, char *file)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(file) + 2))))
		return (-1);
	ft_strcpy(str, path);
	ft_strcat(str, "/");
	ft_strcat(str, file);
	push_str_on_array(rec_dir, str);
	return(1);
}

int					open_directory(char *directory, char *flags)
{
	DIR				*dir;
	struct dirent	*buffer;
	t_file_array	*files;
	t_array_str		*rec_dir;

	if (!(dir = opendir(directory)) || !(files = create_file_array(BASE_ARRAY)))
	{
		perror("ls :");
		return (-1);
	}
	rec_dir = ft_strchr(flags, 'R') ? create_array_str(BASE_ARRAY) : NULL;
	while ((buffer = readdir(dir)))
	{
		if (rec_dir != NULL && buffer->d_type == DT_DIR && buffer->d_name[0] != '.')
			push_directory(rec_dir, directory, buffer->d_name);
		files = push_file(files, init_file_struct(buffer->d_name));
		fill_type(files->array[files->size - 1], buffer->d_type);
	}
	print_file_array(files);
	print_array_str(rec_dir);
	return (0);
}

	//opendir directory
	//
	//while readdir
	//		stat
	//		stocker infos dans struct (donc tableau de struct a allouer (tableau dyn ?))
	//		if dir copier nom + path_directory dans tableau char *
	//
	//write long line or else
	//open dir sur each nom in tab
	//
	//
	//tableau dyn struct
	//OU tableau dyn chaine dyn avec stockage nom ou long line
	//
	//variable stock total lien
