/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redir_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:16:44 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/22 00:18:59 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_builtin_directly(t_cmd *current, t_ms *ms)
{
	if (ft_strncmp(current->cmd, "cd", 3) == 0)
		ms->exit_status = ft_cd_directly(current, ms);
	else if (ft_strncmp(current->cmd, "echo", 5) == 0)
		ms->exit_status = ft_echo_directly(current->arg);
	else if (ft_strncmp(current->cmd, "env", 4) == 0)
		ms->exit_status = ft_env_direct(environ);
	else if (ft_strncmp(current->cmd, "exit", 5) == 0)
		ft_exit_direct(current);
	else if (ft_strncmp(current->cmd, "export", 7) == 0)
		ms->exit_status = ft_export_direct(current);
	else if (ft_strncmp(current->cmd, "pwd", 4) == 0)
		ms->exit_status = ft_pwd_direct(current);
	else if (ft_strncmp(current->cmd, "unset", 6) == 0)
		ms->exit_status = ft_unset_directly(current->arg);
}

void	ft_execute_forked_builtin(t_cmd *current, t_ms *ms)
{
	if (ft_strncmp(current->cmd, "cd", 3) == 0)
		ft_cd_as_forked(current, ms);
	else if (ft_strncmp(current->cmd, "echo", 5) == 0)
		ft_echo_as_forked(current->arg, ms);
	else if (ft_strncmp(current->cmd, "env", 4) == 0)
		ft_env_forked(ms);
	else if (ft_strncmp(current->cmd, "exit", 5) == 0)
	{
		ft_exit_forked(current, ms);
		exit(1);
	}
	else if (ft_strncmp(current->cmd, "export", 7) == 0)
		ft_export_forked(current, ms);
	else if (ft_strncmp(current->cmd, "pwd", 4) == 0)
		ft_pwd_forked(current, ms);
	else if (ft_strncmp(current->cmd, "unset", 6) == 0)
		ft_unset_as_forked(ms, current->arg);
}

void	ft_error(void)
{
	perror("fork");
	exit(1);
}

/* Return 1 if the command is recognized as 
a builtin, 0 otherwise */
int	ft_check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}
