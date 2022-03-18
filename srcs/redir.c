/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:32:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/18 16:51:19 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	redirection(t_vars *vars, char *cmd, int iter)
{	
	vars->pids[iter] = fork();
	if (vars->pipes[iter] == -1)
	{
		perror("pipex");
		cleaner(vars);
		exit(EXIT_FAILURE);
	}
	else if (vars->pids[iter] == 0)
		child_process(vars, cmd, iter);
	else
		waitpid(vars->pipes[iter], NULL, 0);
}
