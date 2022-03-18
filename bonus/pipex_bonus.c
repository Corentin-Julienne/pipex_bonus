/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/16 18:58:36 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	file_opener(t_vars *vars, int type, int ac)
{	
	if (type == IN)
	{
		if (access(vars->av[1], F_OK) != 0)
		{
			perror("pipex: ");
			exit(EXIT_FAILURE);
		}
		vars->fd_in = open(vars->av[1], O_RDONLY);
	}
	else
		vars->fd_out = open(vars->av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
}

static void	waiting_for_children(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->num_of_pipes)
	{
		waitpid(vars->pids[i], NULL, 0);
		i++;
	}
}

static void	pipex(t_vars *vars)
{	
	pipes_activation(vars, vars->num_of_pipes);
	vars->cmds_used = 0;
	while (vars->cmds_used < vars->num_cmds)
	{
		redirection(vars, vars->av[vars->cmds_used + 2], vars->cmds_used);
		vars->cmds_used++;
	}
	close_all_pipes(vars);
	waiting_for_children(vars);
	free(vars->new_paths);
	free(vars);
}

static int	handle_fds(t_vars *vars, int ac)
{
	file_opener(vars, IN, ac);
	if (vars->fd_in == -1)
	{
		free(vars->new_paths);
		free(vars);
		display_err_msg("open");
	}
	file_opener(vars, OUT, ac);
	if (vars->fd_out == -1)
	{
		free(vars->new_paths);
		free(vars);
		if (close(vars->fd_in) == -1)
			display_err_msg("close");
		exit(EXIT_FAILURE);
	}
	pipex(vars);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;

	if (ac < 5)
	{
		ft_putstr_fd("Error : not enough arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		display_err_msg("malloc alloc failure");
	vars->num_of_pipes = ac - 4;
	init_struct(vars, av, env);
	return (handle_fds(vars, ac));
}
