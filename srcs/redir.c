/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:32:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/19 19:22:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int wait_process_and_exit_status(t_vars *vars, int iter)
{
	int		waitpid_status;
	int		rtn_code;
	
	rtn_code = -1;
	waitpid(vars->pipes[iter], &waitpid_status, 0);
	if (WIFEXITED(waitpid_status)) 
        rtn_code = WEXITSTATUS(waitpid_status);
	else if (WIFSIGNALED(waitpid_status))
        rtn_code = WTERMSIG(waitpid_status);
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
	else
	{
		vars->rtn_code = wait_process_and_exit_status(vars, iter);
		printf("exit status of the cmd = %d\n", vars->rtn_code);
	}
}
