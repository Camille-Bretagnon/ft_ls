/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:31:14 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/01 14:21:07 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./libft/libft.h"
#include <pwd.h>
#include <grp.h>

static void		swap(t_file **array, int i, int j)
{
	t_file		*temp;

	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

static void		basic_sort(t_file **array, int size)
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
}

static t_file_array		**fill_stats(t_file **array, unsigned int size, char flag, t_padding *padding)
{
	unsigned int	i;
	struct stat		buffer;

	i = 0;
	while (i < size)
	{
		stat(array[i]->file_name, &buffer);
		padding->nb_blocks += buffer.st_blocks;
		perm = buffer.st_mode;
		links = buffer.st_nlink;
		uid = buffer.st_uid;
		gid = buffer.st_gid;
		if (flag == 0)
			date = buffer.st_mtime;
		else
			date = buffer.statime;
	}

}

//si l actif u ou t sert juste a savoir quel temps afficher, u seul rien, tu sort by last access

t_padding			*sort(t_file **array, unsigned int size, char *flags)
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
}
