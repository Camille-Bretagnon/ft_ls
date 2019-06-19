# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbretagn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/03 16:54:48 by cbretagn          #+#    #+#              #
#    Updated: 2019/06/19 14:44:31 by cbretagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ls

SRC			= parsing.c\
			  get_stats.c\
			  dynamic_string.c\
			  dynamic_arrays.c\
			  dynamic_file_arrays.c\
			  debug_print.c\
			  open_directory.c\
			  basic_string_arrays.c\
			  buffer_fill.c\
			  sort.c\
			  long_buffer.c\
			  main.c

OBJS		:= $(SRC:.c=.o)

LIB_PATH	= libft/libft.a

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

.PHONY		: all clean fclean re

all			: $(NAME)

$(NAME)		: $(OBJS)
	make -C ./libft/
	$(CC) $(CFLAGS) -o $@ $^ $(LIB_PATH)

clean		:
	rm -f $(OBJS)
	make clean -C ./libft/

fclean		: clean
	rm -f $(NAME)
	make fclean -C ./libft/

re 			: fclean all
