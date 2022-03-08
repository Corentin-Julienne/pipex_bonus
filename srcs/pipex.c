/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/08 14:56:40 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	file_opener(char *file, int type)
{	
	if (type == IN)
	{
		if (access(file, F_OK) != 0)
		{
			perror("pipex: ");
			exit(EXIT_FAILURE);
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_RDWR | O_CREAT | O_TRUNC, 0644));
}

void	pipex(t_vars *vars)
{
	if (dup2(vars->fd_in, STDIN_FILENO) == -1
		 || dup2(vars->fd_out, STDOUT_FILENO) == -1)
		cleaner(vars, "dup");
	vars->pipes = (int *)malloc(sizeof(int) * 2);
	if (!vars->pipes)
		cleaner(vars, "pipes array init");
	vars->pids_arr = (pid_t *)malloc(sizeof(pid_t) * 2);
	if (!vars->pids_arr)
		cleaner(vars, "pids array init");
	pipes_activation(vars, 1);
	redirection(vars, vars->av[2], 0);
	cmd_exec(vars, vars->av[3]);
	close_in_and_out(vars->fd_in, vars->fd_out);
	free(vars->new_paths);
	free(vars);
}

int	handle_fds(t_vars *vars)
{
	vars->fd_in = file_opener(vars->av[1], IN);
	if (vars->fd_in == -1)
	{
		free(vars->new_paths);
		free(vars);
		display_err_msg("open");
	}
	vars->fd_out = file_opener(vars->av[4], OUT);
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

	if (ac != 5)
	{
		ft_putstr_fd("Error : Wrong number of arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		display_err_msg("malloc alloc failure");
	init_struct(vars, av, env);
	return (handle_fds(vars));
}
