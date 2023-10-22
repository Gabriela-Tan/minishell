/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:27:11 by mvocasko          #+#    #+#             */
/*   Updated: 2023/10/21 00:42:58 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//function is responsible for printing env variables stored in environ[]
//it iterates through the array and prints each variable to standard output
int	ft_env_direct(char *environ[])
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
//function for a forked process - prints the env variables 
//stored in the environ array to standard output

void	ft_env_forked(t_ms *ms)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	free_and_exit(0, ms);
}
