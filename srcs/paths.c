/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:55:15 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/08 10:57:25 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	handle_slashes_prbl(t_vars *vars, char **paths_v2)
{
	free_problem_split(paths_v2, vars->i);
	free(vars);
	display_err_msg("malloc alloc failure");
}

static void	add_slashes(t_vars *vars, char **paths_v2)
{
	while (vars->paths[vars->i])
	{
		paths_v2[vars->i] = ft_strdup(vars->paths[vars->i]);
		if (!paths_v2[vars->i])
			handle_slashes_prbl(vars, paths_v2);
		paths_v2[vars->i] = ft_strjoin_and_free(paths_v2[vars->i], "/");
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
		free(vars);
		display_err_msg("malloc alloc failure");
	}
	vars->i = 0;
	add_slashes(vars, paths_v2);
	free_split(vars->paths);
	return (paths_v2);
}

char	*join_cmd_to_path(t_vars *vars, char **cmd_args, int i) // check for leaks
{
	char	*path;
	char	*cmd_slash;

	cmd_slash = ft_strchr(cmd_args[0], '/');
	if (cmd_slash && cmd_slash[0] == '/')
		return (cmd_args[0]);
	path = ft_strjoin(vars->new_paths[i], cmd_args[0]);
	if (!path)
		display_err_msg("malloc alloc failure");
	return (path);
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
			paths_str = env[i] + (sizeof(char) * 5);
			break ;
		}
		i++;
	}
	paths = ft_split(paths_str, ':');
	if (!paths)
	{
		free(vars);
		display_err_msg("malloc alloc failure");
	}
	return (paths);
}
