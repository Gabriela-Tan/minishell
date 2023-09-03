/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:04:12 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/03 11:04:59 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array != NULL)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

/* Return 1 if the command is a builtin, 0 otherwise */
int	ft_check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0 || 
		ft_strncmp(cmd, "pwd", 4) == 0 || 
		ft_strncmp(cmd, "cd", 3) == 0 || 
		ft_strncmp(cmd, "env", 4) == 0 || 
		ft_strncmp(cmd, "export", 7) == 0 || 
		ft_strncmp(cmd, "unset", 6) == 0 || 
		ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}