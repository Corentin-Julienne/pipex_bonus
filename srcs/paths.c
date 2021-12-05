/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:55:15 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/05 15:07:18 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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
		return (NULL);
	return (paths);
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
		return (NULL); // change that
	vars->i = 0;
	while (vars->paths[vars->i])
	{
		paths_v2[vars->i] = ft_strdup(vars->paths[vars->i]);
		paths_v2[vars->i] = ft_strjoin_and_free(paths_v2[vars->i], "/");
		vars->i++;
	}
	paths_v2[vars->i] = NULL;
	free_split(vars->paths);
	vars->i = 0;
	return (paths_v2);
}
