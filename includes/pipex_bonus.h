/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:39:06 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/09 12:52:21 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		**pipes;
	pid_t	pids;
	int		num_of_pipes;
}			t_vars;

/* errors.c */

void	display_err_msg(char *err_msg);

/* free.c */

void	cleaner(t_vars *vars, char *err);
void	free_split(char **split);
void	free_problem_split(char **split, int i);
void	close_in_and_out(int fd_in, int fd_out);

/* init_struct.c */

void	init_struct(t_vars *vars, char **av, char **env);

/* paths.c */

char	*join_cmd_to_path(t_vars *vars, char **cmd_args, int i);
char	**paths_with_slash(t_vars *vars);
char	**recup_paths(t_vars *vars);

/* pipes.c */

void	pipes_activation(t_vars *vars, int num_pipes);
int		child_process(t_vars *vars, char *cmd, int iter);
void	redirection(t_vars *vars, char *cmd, int iter);

/* pipex.c */

int		cmd_exec(t_vars *vars, char *cmd);
int		handle_fds(t_vars *vars);
void	file_opener(t_vars *vars, int type);
void	pipex(t_vars *vars);

#endif
