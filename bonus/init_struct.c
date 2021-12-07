/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:40:38 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/06 16:08:25 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus.h"

void	init_struct(t_vars *vars, char **av, char **env)
{
	vars->i = 0;
	vars->av = av;
	vars->env = env;
	vars->paths = recup_paths(vars);
	vars->new_paths = paths_with_slash(vars);
}
