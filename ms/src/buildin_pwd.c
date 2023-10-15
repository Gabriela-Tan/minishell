/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 19:27:43 by mvocasko          #+#    #+#             */
/*   Updated: 2023/10/04 21:49:45 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	ft_pwd_direct(t_cmd *current)
{
	char	cwd[1048];

	(void)current;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror ("getcwd");
		return (1);
	}
}

void	ft_pwd_forked(t_cmd *current, t_ms *ms)
{
	char	cwd[1048];

	(void)current;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
	}
	free_and_exit(0, ms);
}
