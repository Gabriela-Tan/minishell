/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 02:35:10 by mvocasko          #+#    #+#             */
/*   Updated: 2023/10/21 00:46:04 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//handles exit operation within a forked process
//checks the arguments provided in the current structure and 
//exits the process with the specified exit status using exit(status)

void	ft_exit_forked(t_cmd *current, t_ms *ms)
{
	int	status;

	(void)ms;
	if (current->arg[1] != NULL)
	{
		status = ft_atoi(current->arg[1]);
		exit(status);
	}
	else
	{
		exit(0);
	}
}
//same as previous - code should work for both direct and forked processes

void	ft_exit_direct(t_cmd *current)
{
	int	status;

	if (current->arg[1] != NULL)
	{
		status = ft_atoi(current->arg[1]);
		exit(status);
	}
	else
	{
		exit(0);
	}
}
