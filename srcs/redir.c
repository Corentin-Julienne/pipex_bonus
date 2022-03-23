/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:32:11 by cjulienn          #+#    #+#             */
/*   Updated: 2022/03/23 17:35:12 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	wait_process_and_exit_status(t_vars *vars, int iter) // check if necessary
{
	int		waitpid_status;
	int		rtn_code;
	
	rtn_code = -1;
	waitpid(vars->pids[iter], &waitpid_status, 0);
	if (WIFEXITED(waitpid_status))
		rtn_code = WEXITSTATUS(waitpid_status);
	ft_putstr_fd(ft_itoa(rtn_code), STDERR_FILENO);
	if (rtn_code)
		ft_putstr_fd("error of code different from 0\n", STDERR_FILENO);
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
