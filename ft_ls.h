/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:47:18 by cbretagn          #+#    #+#             */
/*   Updated: 2019/06/19 15:09:27 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include "dynamic.h"

# define MAX_FLAGS 6

# define LINKS 5
# define USER 10
# define GROUP 12
# define BLOCKS 7
# define FULL_PERM "rwx"

typedef struct	s_file
{
	char		*file_name;
	char		type;
	time_t		date;
	char		*long_display;
}				t_file;

int				get_flags(char **argv, char *flags);
t_file			**get_paths(char **argv, int argc, int i);
t_file			*init_file_struct(char *name);
void			delete_file_struct(t_file *del);

void			fill_struct(t_file *to_fill, struct stat buffer);

int				open_directory(char *directory, char *flags);

void			basic_sort(t_file **array, int size);

void			write_long_buffer(t_file_array *files, char *flags);
# endif
