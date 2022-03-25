/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:32:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/25 15:38:09 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	wait_process_and_exit_status(t_vars *vars, int iter)
{
	int		waitpid_status;
	int		rtn_code;

	rtn_code = -1;
	if (waitpid(vars->pids[iter], &waitpid_status, 0) == -1)
	{
		cleaner(vars);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
	if (WIFEXITED(waitpid_status) && iter == 1)
		rtn_code = WEXITSTATUS(waitpid_status);
	return (rtn_code);
}

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
}
