/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:31:14 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/04 16:56:32 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./libft/libft.h"

/*static void		swap(t_file **array, int i, int j)
{
	t_file		*temp;

	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}*/

/*static void		basic_sort(t_file **array, int size)
{
	int	i;
	int	j;

	i = 0;
	while (++i < size)
	{
		j = i + 1;
		while (--j > 0 && (ft_strcmp(array[j]->file_name, array[j - 1]->file_name) < 0))
			swap(array, j, j - 1);
	}
}*/
static unsigned int		nb_len(unsigned int nb)
{
	unsigned int		ret;

	ret = 0;
	while (nb != 0)
	{
		nb /= 10;
		ret++;
	}
	return (ret);
}

t_file_array			*fill_stats(t_file_array *files, char flag, t_padding *padding)
{
	unsigned int	i;
	struct stat		buffer;

	i = 0;
	while (i < files->size)
	{
		stat(files->array[i]->file_name, &buffer);
		padding->nb_blocks += buffer.st_blocks;
		padding->links = padding->links < nb_len(buffer.st_nlink) ?
			nb_len(buffer.st_nlink) : padding->links;
		padding->max_size = padding->max_size < nb_len(buffer.st_size) ?
			nb_len(buffer.st_size) : padding->max_size;
		files->array[i]->perm = buffer.st_mode;
		files->array[i]->links = buffer.st_nlink;
		files->array[i]->uid = buffer.st_uid;
		files->array[i]->gid = buffer.st_gid;
		files->array[i]->date = flag == 0 ? buffer.st_mtime : buffer.st_atime;
		files->array[i]->size = buffer.st_size;
		files->array[i]->user = get_username(files->array[i]->uid);
		files->array[i]->group = get_groupname(files->array[i]->gid);
		padding->user = padding->user < ft_strlen(files->array[i]->user) ? 
			ft_strlen(files->array[i]->user) : padding->user;
		padding->group = padding->group < ft_strlen(files->array[i]->group) ? 
			ft_strlen(files->array[i]->group) : padding->group;
		i++;
	}
	return (files);
}

//si l actif u ou t sert juste a savoir quel temps afficher, u seul rien, tu sort by last access

/*t_padding			*sort(t_file **array, unsigned int size, char *flags)
{
	t_padding		*ret;

	ret = NULL;
	if (ft_strchr(flags, 'l'))
	{
		if (!(ret = (t_padding *)malloc(sizeof(t_padding))))
			return (NULL);
		if (ft_strchr(flags, 'u'))
			array = fill_stats(array, size, T_LASTACCESS, ret);
		else
			array = fill_stats(array, size, T_MODIFIED, ret);
	}
	if (ft_strchr(flags, 't'))
	{
		if (ft_strchr(flags, 'u'))
			array = fill_date(array, size, T_LASTACCESS);
		else
			array = fill_date(array, size, T_MODIFIED);
		date_sort(
	}
	else
		basic_sort
	return (ret);
}*/
