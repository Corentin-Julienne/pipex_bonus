/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:55:41 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/08 19:04:39 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	pipes_destruction(t_vars *vars, int num_pipe)
// {
// 	// TODO
// }

void	pipes_activation(t_vars *vars, int num_pipes)
{
	int		i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(vars->pipes + (i * 2)) == -1)
			cleaner(vars, "pipes");
		i++;
	}
}

int	child_process(t_vars *vars, int iter, int cp_num) // check if this works
{
	if (cp_num == FIRST)
	{
		if (close(vars->pipes[iter * 2]) == -1)
			perror("pipex"); // clean
		if (dup2(vars->fd_in, STDIN_FILENO) == -1)
			perror("pipex");
		if (dup2(vars->pipes[(iter * 2) + 1], STDOUT_FILENO) == -1)
			perror("pipex"); // clean
		cmd_exec(vars, vars->av[2]);
	}
	else
	{
		if (close(vars->pipes[(iter * 2) + 1]) == -1)
			perror("pipex"); // clean
		if (dup2(vars->pipes[iter * 2], STDIN_FILENO) == -1)
			perror("pipex"); //clean
		if (dup2(vars->fd_out, STDOUT_FILENO) == -1)
			perror("pipex");
		cmd_exec(vars, vars->av[3]);
	}
	return (0); // check that
}

void	redirection(t_vars *vars, int iter)
{
	vars->pids_arr[iter * 2] = fork();
	if (vars->pids_arr[iter * 2] == -1)
		cleaner(vars, "fork");
	if (vars->pids_arr[iter * 2] == 0)
		child_process(vars, iter, FIRST);
	vars->pids_arr[(iter * 2) + 1] = fork();
	if (vars->pids_arr[(iter * 2) + 1] == -1)
		cleaner(vars, "fork");
	if (vars->pids_arr[(iter * 2) + 1] == 0)
		child_process(vars, iter, SECOND);
	waitpid(vars->pids_arr[iter * 2], NULL, 0);
	waitpid(vars->pids_arr[(iter * 2) + 1], NULL, 0);
}
