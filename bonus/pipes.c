/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:55:41 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/09 12:54:57 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
		vars->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (!vars->pipes[i])
			perror("malloc alloc");
		i++;
	}
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(vars->pipes[i]) == -1)
			perror("pipe");
		i++;
	}
}

void	close_useless_pipes(t_vars *vars, int iter)
{
	int		i;

	i = 0;
	while (i < vars->num_of_pipes)
	{
		if (i != (iter - 1))
		{
			if (close(vars->pipes[i][0]) == -1)
				perror("pipex");
		}
		if (iter != i)
		{
			if (close(vars->pipes[i][1]) == -1)
				perror("pipex");
		}
		i++;
	}
}

void	smart_dup2(t_vars *vars, int iter)
{
	if (iter == 0)
	{
		if (dup2(vars->fd_in, STDIN_FILENO) == -1)
			perror("dup2");
		if (dup2(vars->pipes[0][1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	if (iter == vars->num_of_pipes) // check that
	{
		if (dup2(vars->pipes[iter - 1][0], STDIN_FILENO) == -1)
			perror("dup2");
		if (dup2(vars->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
	}
	else
	{
		if (dup2(vars->pipes[iter - 1][0], STDIN_FILENO) == -1)
			perror("dup2");
		if (dup2(vars->pipes[iter][1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
}

int	child_process(t_vars *vars, char *cmd, int iter) // check if this works
{
	close_useless_pipes(vars, iter);
	smart_dup2(vars, iter);
	cmd_exec(vars, cmd);
	return (0);
}

void	redirection(t_vars *vars, char *cmd, int iter)
{
	vars->pids = fork();
	if (vars->pids == -1)
		cleaner(vars, "fork");
	if (vars->pids == 0)
		child_process(vars, cmd, iter);
	waitpid(vars->pids, NULL, 0);
	printf("go till there\n");
	vars->pids = -1;
}
