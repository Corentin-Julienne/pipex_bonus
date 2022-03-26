/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:40:38 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/26 14:25:55 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	init_pids_arr(t_vars *vars)
{
	pid_t	*pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * vars->num_cmds);
	if (!pids)
	{
		cleaner(vars);
		ft_putstr_fd("pipex : unsuccesful memory allocation\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	vars->pids = pids;
}

void	init_struct(t_vars *vars, char **av, char **env)
{
	vars->i = 0;
	vars->av = av;
	vars->env = env;
	vars->paths = recup_paths(vars);
	vars->new_paths = paths_with_slash(vars);
	vars->pipes = NULL;
	vars->pids = NULL;
	vars->fd_in = -1;
	vars->fd_out = -1;
	vars->num_cmds = vars->num_of_pipes + 1;
	vars->cmds_used = 0;
	init_pids_arr(vars);
}
