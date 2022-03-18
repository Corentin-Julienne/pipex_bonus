/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:56:51 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/16 13:49:04 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	is_path_functionnal(char *path_with_cmd)
{
	if (access(path_with_cmd, R_OK) == 0 && access(path_with_cmd, X_OK) == 0)
		return (0);
	else
	{
		free(path_with_cmd);
		return (1);
	}
}

static char	*join_cmd_to_path(t_vars *vars, char **cmd_args, int i)
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

int	cmd_exec(t_vars *vars, char *cmd)
{
	char		**cmd_args;
	char		*path_with_cmd;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
		cleaner(vars, "malloc alloc error");
	vars->i = 0;
	while (vars->new_paths[vars->i])
	{
		path_with_cmd = join_cmd_to_path(vars, cmd_args, vars->i);
		if (is_path_functionnal(path_with_cmd) == 0)
			execve(path_with_cmd, cmd_args, vars->env);
		vars->i++;
	}
	free_split(cmd_args);
	ft_putstr_fd("pipex : command not found\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
	return (1);
}
