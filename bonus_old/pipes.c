/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 19:14:16 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/07 11:32:20 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus.h"

void	parent_process(pid_t pid, int *pipe_arr)
{
	int		close_fdback;
	int		dup2_fdback;

	close_fdback = close(pipe_arr[1]);
	if (close_fdback == -1)
		handle_errors("close");
	dup2_fdback = dup2(pipe_arr[0], STDIN_FILENO);
	if (dup2_fdback == -1)
		handle_errors("dup2");
	waitpid(pid, NULL, 0);
}

void	child_process(t_vars *vars, int *pipe_arr, char *cmd)
{
	int		close_fdback;
	int		dup2_fdback;

	close_fdback = close(pipe_arr[0]);
	if (close_fdback == -1)
		handle_errors("close");
	dup2_fdback = dup2(pipe_arr[1], STDOUT_FILENO);
	if (dup2_fdback == -1)
		handle_errors("dup2");
	cmd_exec(vars, cmd);
}

void	redirection(t_vars *vars, char *cmd)
{
	int		pipe_output;
	int		pipe_arr[2];
	pid_t	pid;

	pipe_output = pipe(pipe_arr);
	if (pipe_output == -1)
		handle_errors("pipe");
	pid = fork();
	if (pid == -1)
		handle_errors("fork");
	if (pid == 0)
		child_process(vars, pipe_arr, cmd);
	else
		parent_process(pid, pipe_arr);
}
