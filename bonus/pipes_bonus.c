/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:55:41 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/26 14:45:15 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipes_activation(t_vars *vars, int num_pipes)
{
	int		i;
	
	vars->pipes = (int *)malloc(sizeof(int) * vars->num_of_pipes * 2);
	if (!vars->pipes)
	{
		perror("pipex");
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < num_pipes)
	{
		if (pipe(vars->pipes + (2 * i)) == -1)
		{
			perror("pipex");
			cleaner(vars);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	close_all_pipes(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < (vars->num_of_pipes * 2))
	{
		if (close(vars->pipes[i]) == -1)
		{
			perror("pipex");
			cleaner(vars);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
