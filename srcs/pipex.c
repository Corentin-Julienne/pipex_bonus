/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:31:34 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/05 17:46:22 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// void	parse_paths_and_cmds(t_vars *vars, int arg_num)
// {
// 	vars->i = 0;
// 	if (retrieve_path(vars->envp[vars->i]) == 1)
// 		vars->path = vars->envp[vars->i] + (5 * sizeof(char));
// 	vars->i++;
// 	while (vars->envp[vars->i] && retrieve_path(vars->envp[vars->i]) == 0)
// 	{
// 		if (retrieve_path(vars->envp[vars->i]) == 1)
// 			vars->path = vars->envp[vars->i] + (5 * sizeof(char));
// 		vars->i++;
// 	}
// 	vars->paths = ft_split(vars->path, ':');
// 	vars->cmds = ft_split(vars->argv[arg_num], ' ');
// 	vars->i = 0;
// }

void	pipex(int fd_in, int fd_out, t_vars *vars)
{
	int		pipe_output;
	int		pipe_arr[2];
	int		status;
	pid_t	pid;

	pipe_output = pipe(pipe_arr);
	if (pipe_output == -1)
		handle_pipe_and_forks_errors("pipe"); // change that
	pid = fork();
	if (pid == 0) // child process
	{
		close(pipe_arr[0]);
		
	}
	else
	{
		close(pipe_arr[1]);
		waitpid(pid, &status, 0);
	}
}

int	file_opener(char *file, int type)
{
	if (type == IN)
	{
		if (access(file, F_OK) != 0);
		{
			perror("pipex :");
			return (STDIN_FILENO); // ???
		}
		return (open(file, O_RDONLY));
	}
	else
		return (open(file, O_RDWR | O_CREAT | O_TRUNC, 0644));
}

int	main(int ac, char **av, char **env)
{
	int		fd_in;
	int		fd_out;
	t_vars	*vars;

	if (ac != 5) // check that
	{
		ft_putstr_fd("Error : Wrong number of arguments\n", 2);
		return (-1);
	}
	fd_in = file_opener(av[1], IN);
	fd_out = file_opener(av[4], OUT);
	if (fd_in == -1 || fd_out == -1)
		handle_fd_errors(2); // change this
	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (-1); // check this
	init_struct(vars, av, env);
	pipex(fd_in, fd_out, vars);
	free(vars);
	return (0);
}
