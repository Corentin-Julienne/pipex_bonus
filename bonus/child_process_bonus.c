/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:40:57 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/16 18:55:38 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	first_redir(t_vars *vars)
{
	if (dup2(vars->fd_in, STDIN_FILENO) == -1)
		perror("dup2 - 1");
	if (dup2(vars->pipes[1], STDOUT_FILENO) == -1)
		perror("dup2 - 2");
	if (close(vars->fd_in) == -1)
		perror("dup2 - 3");
}

static void last_redir(t_vars *vars, int iter)
{
	if (dup2(vars->fd_out, STDOUT_FILENO) == -1)
		perror("dup2");
	if (dup2(vars->pipes[(iter * 2) - 2], STDIN_FILENO) == -1)
		perror("dup2");
	if (close(vars->fd_out) == -1)
		perror("close");
}

static void	smart_dup2(t_vars *vars, int iter)
{
	if (iter == 0)
		first_redir(vars);
	else if (iter == vars->num_of_pipes)
		last_redir(vars, iter);
	else
	{
		if (dup2(vars->pipes[(iter * 2) - 2], STDIN_FILENO) == -1)
			perror("dup2 - 3");
		if (dup2(vars->pipes[(iter * 2) + 1], STDOUT_FILENO) == -1)
			perror("dup2 - 4");
	}
}

void	close_useless_pipes(t_vars *vars, int iter)
{
	int			i;
	
	i = 0;
	while (iter == 0 && i < vars->num_of_pipes * 2)
	{
		if (i != 1)
		{
			if (close(vars->pipes[i]) == -1)
				perror("close"); // handle error
		}
		i++;
	}
	while (iter > 0 && i < vars->num_of_pipes * 2)
	{
		if (i != ((iter * 2) - 2) && i != ((iter * 2) + 1))
		{
			if (close(vars->pipes[i]) == -1)
				perror("close"); // handle error
		}
		i++;
	}
}

int	child_process(t_vars *vars, char *cmd, int iter) // check if this works
{
	close_useless_pipes(vars, iter);
	smart_dup2(vars, iter);
	cmd_exec(vars, cmd);
	return (0);
}
