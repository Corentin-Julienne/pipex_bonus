/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:29:52 by cjulienn          #+#    #+#             */
/*   Updated: 2021/12/07 11:31:19 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bonus.h"

void	handle_fd_errors(int fd_num)
{
	if (fd_num == 1)
		ft_putstr_fd("pipex : Error : infile cannot be openned\n", 2);
	else
		ft_putstr_fd("pipex : Error : outfile cannot be openned\n", 2);
	exit(EXIT_FAILURE);
}

void	handle_errors(char *error_type)
{
	ft_putstr_fd("there is a ", STDERR_FILENO);
	ft_putstr_fd(error_type, STDERR_FILENO);
	ft_putstr_fd(" error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	handle_malloc_errors(void)
{
	ft_putstr_fd("pipex: Error : unsuccesful memory alloc\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	handle_ac_errors(t_vars *vars)
{
	ft_putstr_fd("pipex : Wrong number of arguments\n", STDERR_FILENO);
	free(vars);
	exit(EXIT_FAILURE);
}
