/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:55:15 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/24 17:00:44 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	handle_slashes_prbl(t_vars *vars, char **paths_v2) // pb with fds
{
	free_problem_split(paths_v2, vars->i);
	free_split(vars->paths);
	close_in_and_out(vars->fd_in, vars->fd_out);
	free(vars);
	ft_putstr_fd("pipex : unsuccesful memory allocation\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	add_slashes(t_vars *vars, char **paths_v2)
{
	char	*tmp;
	
	while (vars->paths[vars->i])
	{
		paths_v2[vars->i] = ft_strdup(vars->paths[vars->i]);
		if (!paths_v2[vars->i])
			handle_slashes_prbl(vars, paths_v2);
		tmp = ft_strjoin(paths_v2[vars->i], "/");
		if (!tmp)
		{
			free(paths_v2[vars->i]);
			handle_slashes_prbl(vars, paths_v2);
		}
		free(paths_v2[vars->i]);
		paths_v2[vars->i] = tmp;
		if (!paths_v2[vars->i])
			handle_slashes_prbl(vars, paths_v2);
		vars->i++;
	}
	paths_v2[vars->i] = NULL;
}

char	**paths_with_slash(t_vars *vars)
{
	size_t	arr_len;
	char	**paths_v2;

	arr_len = 0;
	while (vars->paths[arr_len])
		arr_len++;
	paths_v2 = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (!paths_v2)
	{
		free_split(vars->paths);
		free(vars);
		ft_putstr_fd("pipex : unsuccesful memory allocation\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars->i = 0;
	add_slashes(vars, paths_v2);
	free_split(vars->paths);
	return (paths_v2);
}

char	**recup_paths(t_vars *vars)
{
	char	**paths;
	char	**env;
	char	*paths_str;
	size_t	i;

	env = vars->env;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			paths_str = env[i] + 5;
			break ;
		}
		i++;
	}
	paths = ft_split(paths_str, ':');
	if (!paths)
	{
		free(vars);
		ft_putstr_fd("pipex : unsuccesful memory allocation\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (paths);
}
