/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:52:54 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/06 19:01:11 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_split(char **split)
{
	size_t		i;

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
	size_t		j;
	while (j < i)
	{
		free(split[j]);
		j++;
	}
	free(split);
}

void	close_in_and_out(int fd_in, int fd_out)
{
	int		fd_in_fdback;
	int		fd_out_fdback;
	
	fd_in_fdback = close(fd_in);
	fd_out_fdback = close(fd_out);
	if (fd_in_fdback == -1)
		ft_putstr_fd("Error : input fd could not be closed\n", 2);
	if (fd_out_fdback == -1)
		ft_putstr_fd("Error : output fd could not be closed\n", 2);
}
