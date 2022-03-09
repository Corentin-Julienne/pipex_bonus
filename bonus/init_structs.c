/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:40:38 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/09 10:17:14 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_struct(t_vars *vars, char **av, char **env)
{
	vars->i = 0;
	vars->av = av;
	vars->env = env;
	vars->paths = recup_paths(vars);
	vars->new_paths = paths_with_slash(vars);
	vars->pipes = NULL;
	vars->pids = -1;
	vars->fd_in = -1;
	vars->fd_out = -1;
}
