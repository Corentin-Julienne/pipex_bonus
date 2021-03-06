/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/25 15:09:29 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	leaks_killer(void)
// {
// 	system("leaks pipex");
// 	exit(EXIT_FAILURE);
// }

static void	file_opener(t_vars *vars, int type)
{	
	if (type == IN)
	{
		if (access(vars->av[1], F_OK) != 0)
		{
			perror("pipex");
			cleaner(vars);
			exit(EXIT_FAILURE);
		}
		vars->fd_in = open(vars->av[1], O_RDONLY);
	}
	else
		vars->fd_out = open(vars->av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
}

static int	pipex(t_vars *vars)
{
	int			pipeline[2];
	int			rtn_code;

	if (pipe(pipeline) == -1)
	{
		perror("pipex");
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	vars->pipes = pipeline;
	redirection(vars, vars->av[2], 0);
	redirection(vars, vars->av[3], 1);
	if (close(pipeline[0]) == -1)
		perror("pipex");
	if (close(pipeline[1]) == -1)
		perror("pipex");
	vars->rtn_code = wait_process_and_exit_status(vars, 0);
	vars->rtn_code = wait_process_and_exit_status(vars, 1);
	rtn_code = vars->rtn_code;
	cleaner(vars);
	return (rtn_code);
}

static int	handle_fds(t_vars *vars)
{
	int			rtn_code;

	file_opener(vars, IN);
	if (vars->fd_in == -1)
	{
		perror("pipex");
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	file_opener(vars, OUT);
	if (vars->fd_out == -1)
	{
		perror("pipex");
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	rtn_code = pipex(vars);
	return (rtn_code);
}

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;

	if (ac != 5)
	{
		ft_putstr_fd("pipex : wrong number of arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
	{
		ft_putstr_fd("pipex : unsuccesful memory allocation\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	init_struct(vars, av, env);
	return (handle_fds(vars));
}
