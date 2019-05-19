/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:47:18 by cbretagn          #+#    #+#             */
/*   Updated: 2019/05/19 18:29:19 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <sys/stat.h>

# define MAX_FLAGS 6

typedef struct	s_file
{
	char		*file_name;
	char		type;
	char		*date;
	char		*long_display;
}				t_file;

int				get_flags(char **argv, char *flags);
t_file			**get_paths(char **argv, int argc, int i);
t_file			*init_file_struct(char *name);

void			fill_struct(t_file *to_fill, struct stat buffer);
# endif
