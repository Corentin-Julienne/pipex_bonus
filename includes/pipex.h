/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:39:06 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/05 16:13:07 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#define IN		0
#define OUT		1

typedef struct	s_vars
{
	int		i;
	int		j;

	char	**av;
	char	**env;
	char	**paths;
	char	**new_paths;

	char	**cmds;
	char	*cmd;
	
}			t_vars;

/* errors.c */

void	handle_fd_errors(int fd_num);
void	handle_pipe_and_forks_errors(char *error_type);
void	handle_dup2_errors(char *error_type);

// // free function (fake for now)

/* init_struct.c */

void	init_struct(t_vars *vars, char **av, char **env);

/* paths.c */

char	**recup_paths(t_vars *vars);
char	**paths_with_slash(t_vars *vars);

/* pipex.c */

void	pipex(int fd_1, int fd_2, t_vars *vars);
void	parse_paths_and_cmds(t_vars *vars, int arg_num);

#endif