/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:47:18 by cbretagn          #+#    #+#             */
/*   Updated: 2019/08/12 13:09:27 by cbretagn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"
#include "dynamic.h"

#include <sys/wait.h>

# define MAX_FLAGS 6

# define T_MODIFIED 0
# define T_LASTACCESS 1

typedef struct	s_file
{
	char			*file_name;
	char			*type;
	mode_t			perm;
	nlink_t			links;
	uid_t			uid;
	gid_t			gid;
	dev_t			device;
	char			*user;
	char			*group;
	unsigned int	size;
	struct timespec	date;
}				t_file;

int				get_flags(char **argv, char *flags);
t_file			**get_paths(char **argv, int argc, int i);
t_file			*init_file_struct(char *name, char free);
void			delete_file_struct(t_file *del);
void			delete_simple_file_struct_array(t_file **to_del);

void			fill_struct(t_file *to_fill, struct stat buffer);
void			fill_type(t_file *to_fill, mode_t mode);

int				open_directory(char *directory, char *flags);

char			*get_username(uid_t uid);
char			*get_groupname(gid_t gid);
void			malloc_error(void);
char			*timetoa(time_t date);
int				is_hidden(char *file);

void			sort_files(t_file **array, int size, char *flags);

void			write_paths_infos(t_file **paths, char *flags, struct s_padding *padding);
void			print_directory(char *directory);

unsigned int	nb_len(unsigned int nb);
# endif
