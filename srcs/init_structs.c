/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:40:38 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/24 17:02:08 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	init_pids_arr(t_vars *vars)
{
	pid_t	*pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * 2);
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
	init_pids_arr(vars);
}
