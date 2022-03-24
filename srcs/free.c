/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:52:54 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/24 14:42:28 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/* use cleaner function in case of pb and free vars completely and close fds */

void	cleaner(t_vars *vars)
{
	free_split(vars->new_paths);
	if (vars->pids != NULL)
		free(vars->pids);
	close_in_and_out(vars->fd_in, vars->fd_out);
	free(vars);
}

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_problem_split(char **split, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free(split);
}

void	close_in_and_out(int fd_in, int fd_out)
{	
	if (fd_in != -1)
	{
		if (close(fd_in) == -1)
			perror("pipex 1");
	}
	if (fd_out != -1)
	{
		if (close(fd_out) == -1)
			perror("pipex 2");
	}
}
