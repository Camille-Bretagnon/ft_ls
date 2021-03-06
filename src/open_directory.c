/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_directory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:32:04 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/16 15:28:28 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

static t_file_array	*push_directory(t_file_array *rec_dir, char *path,
		char *file, char *time)
{
	char			*str;
	t_file			*new_dir;
	struct stat		buffer;
	int				len;

	len = ft_strlen(path);
	if (!(str = ft_strnew(len + ft_strlen(file) + 1)))
		malloc_error();
	ft_strcpy(str, path);
	if (path[len - 1] != '/')
		ft_strcat(str, "/");
	ft_strcat(str, file);
	if (!(new_dir = init_file_struct(str, 1)))
		malloc_error();
	stat(str, &buffer);
	new_dir->date = time ? buffer.st_atimespec : buffer.st_mtimespec;
	rec_dir = push_file(rec_dir, new_dir);
	return (rec_dir);
}

static t_file_array	*read_directory(struct dirent *buffer,
		t_file_array *files, char *directory)
{
	char		*full_name;
	int			i;

	i = ft_strlen(directory);
	if (!(full_name = ft_strnew(i + ft_strlen(buffer->d_name) + 1)))
		malloc_error();
	ft_strcpy(full_name, directory);
	*(full_name + i) = '/';
	ft_strcpy(full_name + i + 1, buffer->d_name);
	files = push_file(files, init_file_struct(full_name, 1));
	if (buffer->d_type == DT_LNK)
		files->array[files->size - 1]->type[0] = 'l';
	return (files);
}

static int			print_error(void)
{
	perror("ls");
	return (-1);
}

static void			recursive_call(t_file_array *rec_dir, char *flags)
{
	unsigned int	i;

	write(1, "\n", 1);
	if (rec_dir == NULL)
		return ;
	i = 0;
	sort_files(rec_dir->array, rec_dir->size, flags);
	while (i < rec_dir->size)
	{
		print_directory(rec_dir->array[i]->file_name);
		open_directory(rec_dir->array[i]->file_name, flags);
		i++;
	}
	delete_file_array(rec_dir);
}

int					open_directory(char *directory, char *flags)
{
	DIR				*dir;
	struct dirent	*buffer;
	t_file_array	*files;
	t_file_array	*rec_dir;

	if (!(dir = opendir(directory)))
		return (print_error());
	files = create_file_array(BASE_ARRAY);
	rec_dir = ft_strchr(flags, 'R') ? create_file_array(BASE_ARRAY) : NULL;
	while ((buffer = readdir(dir)))
	{
		if (rec_dir != NULL && buffer->d_type == DT_DIR)
		{
			if ((buffer->d_name[0] != '.') || (ft_strchr(flags, 'a')
				&& buffer->d_name[1] != '\0' && buffer->d_name[1] != '.'))
				rec_dir = push_directory(rec_dir, directory,
					buffer->d_name, ft_strchr(flags, 'u'));
		}
		files = read_directory(buffer, files, directory);
	}
	write_buffer(files, flags);
	closedir(dir);
	recursive_call(rec_dir, flags);
	return (0);
}
