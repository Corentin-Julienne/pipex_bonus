# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 17:55:02 by cjulienn          #+#    #+#              #
#    Updated: 2021/12/07 11:14:09 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex

SRCS = ./srcs/errors.c \
	   ./srcs/free.c \
	   ./srcs/init_structs.c \
	   ./srcs/paths.c \
	   ./srcs/pipes.c \
	   ./srcs/pipex.c

BONUS_SRCS = ./bonus/bonus.c \
			 ./bonus/errors.c \
			 ./bonus/free.c \
			 ./bonus/init_struct.c \
			 ./bonus/paths.c \
			 ./bonus/pipes.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

INCLUDE_PATH = ./includes/
BONUS_INC_PATH = ./bonus/
LIBFT_LIB = libft.a

LIBFT_PATH = ./libft/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_PATH)
BONUS_CFLAGS = -Wall -Wextra -Werror -I$(BONUS_INC_PATH)

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

bonus: $(BONUS_OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	cp ./libft/libft.a .
	$(CC) $(BONUS_CFLAGS) $(BONUS_OBJS) -L. -lft -o $(BONUS_NAME)
	@echo pipex[bonus] successfully made !!!

bonus_clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	$(RM) $(BONUS_OBJS)

bonus_fclean: bonus_clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(RM) $(BONUS_NAME)
	$(RM) libft.a

bonus_re: bonus_fclean bonus

.PHONY: all clean fclean re bonus bonus_clean bonus_fclean bonus_re
