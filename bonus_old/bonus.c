/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 16:08:35 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/07 11:31:02 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus.h"

void	cmd_exec(t_vars *vars, char *cmd)
{
	char		**cmd_args;
	char		*path_with_cmd;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		handle_malloc_errors();
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
}

int	file_opener(char *file, int type)
{
	if (type == IN)
	{
		if (access(file, F_OK) != 0)
		{
			perror("pipex ");
			exit(EXIT_FAILURE);
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_RDWR | O_CREAT | O_TRUNC, 0644));
}

void	pipex(t_vars *vars, int fd_in, int fd_out, int ac)
{
	int		i;
	int		dup2_fdback_1;
	int		dup2_fdback_2;

	dup2_fdback_1 = dup2(fd_in, STDIN_FILENO);
	dup2_fdback_2 = dup2(fd_out, STDOUT_FILENO);
	if (dup2_fdback_1 == -1 || dup2_fdback_2 == -1)
		handle_errors("dup2");
	i = 2;
	while (i < ac - 2)
	{
		redirection(vars, vars->av[i]);
		i++;
	}
	cmd_exec(vars, vars->av[ac - 2]);
}

int	main(int ac, char **av, char **env)
{
	t_vars		*vars;
	int			fd_in;
	int			fd_out;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		handle_malloc_errors();
	init_struct(vars, av, env);
	if (ac >= 5)
	{
		fd_in = file_opener(vars->av[1], IN);
		if (fd_in == -1)
			handle_fd_errors(1);
		fd_out = file_opener(vars->av[ac - 1], OUT);
		if (fd_out == -1)
			handle_fd_errors(2);
		pipex(vars, fd_in, fd_out, ac);
	}
	else
		handle_ac_errors(vars);
	free(vars);
	return (0);
}
