/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:39:06 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/26 14:17:23 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# define IN		0
# define OUT	1

typedef struct s_vars
{
	int		i;
	char	**av;
	char	**env;
	char	**paths;
	char	**new_paths;
	int		fd_in;
	int		fd_out;
	int		*pipes;
	pid_t	*pids;
	int		rtn_code;
}			t_vars;

/* child_process.c */

int		child_process(t_vars *vars, char *cmd, int iter);

/* exec.c */

void	cmd_exec(t_vars *vars, char *cmd);

/* free.c */

void	cleaner(t_vars *vars);
void	child_cleaner(t_vars *vars);
void	free_split(char **split);
void	free_problem_split(char **split, int i);
void	close_in_and_out(int fd_in, int fd_out);

/* init_struct.c */

void	init_struct(t_vars *vars, char **av, char **env);

/* paths.c */

char	**paths_with_slash(t_vars *vars);
char	**recup_paths(t_vars *vars);

/* pipes.c */

void	pipes_activation(t_vars *vars, int num_pipes);

/* redir.c */

int		wait_process_and_exit_status(t_vars *vars, int iter);
void	redirection(t_vars *vars, char *cmd, int iter);

void	leaks_killer(void); // kill after

#endif
