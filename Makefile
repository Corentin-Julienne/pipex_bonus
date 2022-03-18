# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/23 17:55:02 by cjulienn          #+#    #+#              #
#    Updated: 2022/03/18 17:00:06 by cjulienn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS_NAME = pipex_bonus

SRCS = ./srcs/child_process.c \
		./srcs/exec.c \
		./srcs/free.c \
		./srcs/init_structs.c \
		./srcs/paths.c \
		./srcs/pipex.c \
		./srcs/redir.c

BONUS_SRCS = ./bonus/child_process_bonus.c \
			 ./bonus/errors_bonus.c \
			 ./bonus/exec_bonus.c \
			 ./bonus/free_bonus.c \
			 ./bonus/init_structs_bonus.c \
			 ./bonus/paths_bonus.c \
			 ./bonus/pipes_bonus.c \
			 ./bonus/pipex_bonus.c \
			 ./bonus/redir_bonus.c

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
