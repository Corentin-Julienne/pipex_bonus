/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:42:32 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/10 18:08:38 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	init_pids_arr(t_vars *vars)
{
	pid_t	*pids;

	pids = (pid_t *)malloc(sizeof(pid_t) * vars->num_of_pipes);
	if (!pids)
		perror("malloc error");
	vars->pids = pids;
}

void	redirection(t_vars *vars, char *cmd, int iter)
{
		init_pids_arr(vars);
		vars->pids[iter] = fork();
		if (vars->pids[iter] == -1)
			cleaner(vars, "fork");
		else if (vars->pids[iter] == 0)
			child_process(vars, cmd, iter);
}
