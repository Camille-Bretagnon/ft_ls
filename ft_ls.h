/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:47:18 by cbretagn          #+#    #+#             */
/*   Updated: 2019/07/01 14:21:14 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "dynamic.h"

# define MAX_FLAGS 6

# define T_MODIFIED 0
# define T_LASTACCESS 1

# define LINKS 5
# define BLOCKS 7
# define FULL_PERM "rwx"

typedef struct	s_file
{
	char		*file_name;
	char		type;
	mode_t		perm;
	nlink_t		links;
	uid_t		uid;
	gid_t		gid;
	char		*username;
	char		*groupname;
	time_t		date;
}				t_file;

typedef	struct	s_padding
{
	unsigned int 	links;
	unsigned int	username;
	unsigned int	groupname;
	unsigned long	nb_blocks;
}				t_padding;

int				get_flags(char **argv, char *flags);
t_file			**get_paths(char **argv, int argc, int i);
t_file			*init_file_struct(char *name);
void			delete_file_struct(t_file *del);

void			fill_struct(t_file *to_fill, struct stat buffer);

int				open_directory(char *directory, char *flags);

t_padding		*sort(t_file **array, int size, char *flags);
void			init_padding(t_paddin *padding);

# endif
