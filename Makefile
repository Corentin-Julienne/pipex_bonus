# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 17:55:02 by cjulienn          #+#    #+#              #
#    Updated: 2021/10/27 11:44:08 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = ./srcs/pipex.c \
	   ./srcs/errors.c \
	   ./srcs/paths.c \
	   ./srcs/init_struct.c

OBJS = $(SRCS:.c=.o)

INCLUDE_PATH = ./includes/
LIBFT_LIB = libft.a

LIBFT_PATH = ./libft/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_PATH)

RM = rm -f

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	cp ./libft/libft.a .
	$(CC) $(CFLAGS) $(OBJS) -L. -lft -o $(NAME)
	@echo pipex successfully made !!!

all: 
	$(NAME)

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(OBJS)
	
fclean:	clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(NAME)
	$(RM) libft.a

re:	fclean all

.PHONY: all clean fclean re
