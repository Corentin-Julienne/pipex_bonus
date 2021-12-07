/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:01:21 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/07 11:34:31 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# define IN		0
# define OUT	1

typedef struct s_vars
{
	int		i;
	char	**av;
	char	**env;
	char	**paths;
	char	**new_paths;
}			t_vars;

/* bonus.c */

void	cmd_exec(t_vars *vars, char *cmd);
int		file_opener(char *file, int type);
void	pipex(t_vars *vars, int fd_in, int fd_out, int ac);

/* errors.c */

void	handle_fd_errors(int fd_num);
void	handle_errors(char *error_type);
void	handle_malloc_errors(void);
void	handle_ac_errors(t_vars *vars);

/* free.c */

void	free_split(char **split);

/* init_struct.c */

void	init_struct(t_vars *vars, char **av, char **env);

/* paths.c */

char	*join_cmd_to_path(t_vars *vars, char **cmd_args, int i);
char	**paths_with_slash(t_vars *vars);
char	**recup_paths(t_vars *vars);

/* pipes.c */

void	parent_process(pid_t pid, int *pipe_arr);
void	child_process(t_vars *vars, int *pipe_arr, char *cmd);
void	redirection(t_vars *vars, char *cmd);

#endif
