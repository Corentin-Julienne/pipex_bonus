/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:39:06 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/07 10:23:06 by cjulienn         ###   ########.fr       */
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
}			t_vars;

/* errors.c */

void	handle_fd_errors(int fd_num);
void	handle_errors(char *error_type);
void	handle_malloc_errors(void);

/* free.c */

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

int		parent_process(t_vars *vars, pid_t pid, int *pipe_arr);
int		child_process(t_vars *vars, int *pipe_arr, char *cmd);
void	redirection(t_vars *vars, char *cmd);

/* pipex.c */

int		cmd_exec(t_vars *vars, char *cmd);
int		file_opener(char *file, int type);
void	pipex(int fd_in, int fd_out, t_vars *vars, int ac);

#endif
