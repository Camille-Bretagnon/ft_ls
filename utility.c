/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:13:15 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/01 14:14:45 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		init_padding(t_padding *padding)
{
	padding->links = 0;
	padding->username = 0;
	padding->groupname = 0;
	padding->nb_blocks = 0;
}
