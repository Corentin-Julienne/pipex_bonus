/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/07 10:49:21 by cjulienn         ###   ########.fr       */
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
		handle_malloc_errors();
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
	int		fd_in;
	int		fd_out;
	
	if (type == IN)
	{
		if (access(file, F_OK) != 0)
		{
			perror("pipex ");
			exit(EXIT_FAILURE);
		}
		fd_in = open(file, O_RDONLY);
		return (fd_in);
	}
	else
	{
		fd_out = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		return (fd_out);
	}
}

void	pipex(int fd_in, int fd_out, t_vars *vars, int ac)
{
	if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
	{
		free(vars->new_paths);
		close_in_and_out(vars->fd_in, vars->fd_out);
		free(vars);
		handle_errors("dup2");
	}
	vars->fd_in = STDIN_FILENO;
	vars->fd_out = STDOUT_FILENO;
	redirection(vars, vars->av[2]);
	cmd_exec(vars, vars->av[3]);
	close_in_and_out(vars->fd_in, vars->fd_out); // check if necessary
	free(vars->new_paths);
	free(vars);
}

int	handle_fds(int ac, char **av, char **env, t_vars *vars)
{
	int		fd_in;
	int		fd_out;

	fd_in = file_opener(av[1], IN);
	if (fd_in == -1)
	{
		free(vars->new_paths);
		free(vars);
		exit(EXIT_FAILURE);
	}
	fd_out = file_opener(av[4], OUT);
	if (fd_out == -1)
	{
		free(vars->new_paths);
		free(vars);
		if (close(fd_in) == -1)
			handle_fd_errors(1);
		exit(EXIT_FAILURE);
	}
	vars->fd_in = fd_in;
	vars->fd_out = fd_out;
	pipex(fd_in, fd_out, vars, ac);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;

	if (ac != 5)
	{
		ft_putstr_fd("Error : Wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		handle_malloc_errors();
	init_struct(vars, av, env);
	return (handle_fds(ac, av, env, vars));
}
