/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:27:00 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/25 14:15:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	first_redir(t_vars *vars)
{
	if (dup2(vars->fd_in, STDIN_FILENO) == -1)
	{
		child_cleaner(vars);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	if (dup2(vars->pipes[1], STDOUT_FILENO) == -1)
	{
		child_cleaner(vars);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

static void	last_redir(t_vars *vars)
{
	if (dup2(vars->pipes[0], STDIN_FILENO) == -1)
	{
		child_cleaner(vars);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	if (dup2(vars->fd_out, STDOUT_FILENO) == -1)
	{
		child_cleaner(vars);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}

static void	smart_dup2(t_vars *vars, int iter)
{
	if (iter == 0)
		first_redir(vars);
	else
		last_redir(vars);
}

int	child_process(t_vars *vars, char *cmd, int iter)
{
	if (iter == 0)
	{
		if (close(vars->pipes[0]) == -1)
			perror("pipex");
	}
	else
	{
		if (close(vars->pipes[1]) == -1)
			perror("pipex");
	}
	smart_dup2(vars, iter);
	cmd_exec(vars, cmd);
	return (0);
}
