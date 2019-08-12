/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:13:15 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/12 16:31:37 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./libft/libft.h"
#include <stdlib.h>

t_padding			*init_padding(void)
{
	t_padding		*ret;

	if (!(ret = (t_padding *)malloc(sizeof(t_padding))))
		malloc_error();
	ret->links = 1;
	ret->user = 0;
	ret->group = 0;
	ret->max_major = -1;
	ret->nb_blocks = 0;
	ret->max_size = 0;
	return (ret);
}

void				delete_padding(t_padding *padding)
{
	free(padding);
	padding = NULL;
}

char				*get_username(uid_t uid)
{
	struct passwd	*name;
	char			*ret;

	name = getpwuid(uid);
	if (!(name->pw_name))
		malloc_error();
	if (!(ret = ft_strnew(ft_strlen(name->pw_name))))
		malloc_error();
	ft_strcpy(ret, name->pw_name);
	return (ret);
}

char				*get_groupname(gid_t gid)
{
	struct group	*group;
	char			*ret;

	group = getgrgid(gid);
	if (!(group->gr_name))
		malloc_error();
	if (!(ret = ft_strnew(ft_strlen(group->gr_name))))
		malloc_error();
	ft_strcpy(ret, group->gr_name);
	return (ret);
}

void				malloc_error(void)
{
	ft_putstr("ls : malloc error, so sorry :/\n");
	exit(-1);
}
