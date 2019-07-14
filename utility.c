/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:13:15 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/14 14:56:24 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./libft/libft.h"
#include <stdlib.h>

t_padding			*init_padding()
{
	t_padding		*ret;
	if (!(ret = (t_padding *)malloc(sizeof(t_padding))))
		return (NULL);
	ret->links = 1;
	ret->user = 0;
	ret->group = 0;
	ret->nb_blocks = 0;
	ret->max_size = 0;
	return (ret);
}

char				*get_username(uid_t uid)
{
	struct passwd 	*name;
	char			*ret;

	name = getpwuid(uid);
	if (!(name->pw_name))
		return (NULL);
	if (!(ret = ft_strnew(ft_strlen(name->pw_name))))
		return (NULL);
	ft_strcpy(ret, name->pw_name);
	return (ret);
}

char				*get_groupname(gid_t gid)
{
	struct group 	*group;
	char			*ret;

	group = getgrgid(gid);
	if (!(group->gr_name))
		return (NULL);
	if (!(ret = ft_strnew(ft_strlen(group->gr_name))))
		return (NULL);
	ft_strcpy(ret, group->gr_name);
	return (ret);
}

void				malloc_error(void)
{
	ft_putstr("ls : malloc error error, so sorry :/\n");
	exit(0);
}
