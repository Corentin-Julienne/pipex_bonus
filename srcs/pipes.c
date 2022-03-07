/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:55:41 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/07 10:21:10 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parent_process(t_vars *vars, pid_t pid, int *pipe_arr)
{
	int		error_code;
	
	error_code = 0;
	if (close(pipe_arr[1]) == -1)
		error_code = 1;
	if (dup2(pipe_arr[0], STDIN_FILENO) == -1)
		error_code = 1;
	waitpid(pid, NULL, 0);
	return (error_code);
}

int	child_process(t_vars *vars, int *pipe_arr, char *cmd)
{
	int		error_code;
	
	error_code = 0;
	if (close(pipe_arr[0]) == -1)
		error_code = 1;
	if (dup2(pipe_arr[1], STDOUT_FILENO) == -1)
		error_code = 1;
	if (error_code != 0)
		return (error_code);
	cmd_exec(vars, cmd);
}

void	redirection(t_vars *vars, char *cmd)
{
	int		pipe_arr[2];
	pid_t	pid;

	if (pipe(pipe_arr) == -1)
	{
		close_in_and_out(vars->fd_in, vars->fd_out);
		free(vars);
		free(vars->new_paths);
		handle_errors("pipe");
	}
	pid = fork();
	if (pid == -1)
	{
		close_in_and_out(vars->fd_in, vars->fd_out);
		free(vars);
		free(vars->new_paths);
		handle_errors("fork");
	}
	if (pid == 0)
		child_process(vars, pipe_arr, cmd);
	else
		parent_process(vars, pid, pipe_arr);
}
