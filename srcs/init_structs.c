/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:40:38 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/05 15:14:47 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	init_struct(t_vars *vars, char **av, char **env)
{
	vars->i = 0;
	vars->j = 0;
	vars->av = av;
	vars->env = env;
	vars->paths = recup_paths(vars);
	vars->new_paths = paths_with_slash(vars);
	vars->cmds = ;
}