/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/19 18:13:44 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// static void	track_leaks(void) // kill after
// {
// 	system("leaks pipex");
// }

static void	file_opener(t_vars *vars, int type)
{	
	if (type == IN)
	{
		if (access(vars->av[1], F_OK) != 0)
		{
			perror("pipex 3");
			cleaner(vars);
			exit(EXIT_FAILURE);
		}
		vars->fd_in = open(vars->av[1], O_RDONLY);
	}
	else
		vars->fd_out = open(vars->av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
}

static void	pipex(t_vars *vars)
{
	int			pipeline[2];
	
	if (pipe(pipeline) == -1)
	{
		perror("pipex 4");
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	vars->pipes = pipeline;
	redirection(vars, vars->av[2], 0);
	redirection(vars, vars->av[3], 1);
	close_in_and_out(vars->fd_in, vars->fd_out);
	cleaner(vars);
}

static int	handle_fds(t_vars *vars)
{
	file_opener(vars, IN);
	if (vars->fd_in == -1)
	{
		perror("pipex 5");
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	file_opener(vars, OUT);
	if (vars->fd_out == -1)
	{
		perror("pipex 6");
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	pipex(vars);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_vars	*vars;

	// atexit(&track_leaks); // suppress after use
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
