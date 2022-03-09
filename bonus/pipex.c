/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/09 12:50:49 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	cmd_exec(t_vars *vars, char *cmd)
{
	char		**cmd_args;
	char		*path_with_cmd;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
	{
		free(vars);
		free(vars->new_paths);
		display_err_msg("malloc alloc failure");
		return (1);
	}
	vars->i = 0;
	while (vars->new_paths[vars->i])
	{
		path_with_cmd = join_cmd_to_path(vars, cmd_args, vars->i);
		execve(path_with_cmd, cmd_args, vars->env);
		vars->i++;
		free(path_with_cmd);
	}
	free_split(cmd_args);
	ft_putstr_fd("pipex : command not found\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
	return (1);
}

void	file_opener(t_vars *vars, int type)
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
		vars->fd_out = open(vars->av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
}

void	pipex(t_vars *vars) // modified
{
	int			i;
	
	vars->pipes = (int **)malloc(sizeof(int *) * vars->num_of_pipes);
	if (!vars->pipes)
		cleaner(vars, "pipes array init");
	pipes_activation(vars, vars->num_of_pipes);
	i = 0;
	while (i < vars->num_of_pipes)
	{
		redirection(vars, vars->av[i + 2], i);
		i++;
	}	
	// close_in_and_out(vars->fd_in, vars->fd_out);
	free(vars->new_paths);
	free(vars);
}

int	handle_fds(t_vars *vars) // is the same
{
	file_opener(vars, IN);
	if (vars->fd_in == -1)
	{
		free(vars->new_paths);
		free(vars);
		display_err_msg("open");
	}
	file_opener(vars, OUT);
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

int	main(int ac, char **av, char **env) // modified
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
	init_struct(vars, av, env);
	vars->num_of_pipes = ac - 4;
	return (handle_fds(vars));
}
