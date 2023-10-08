/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redir_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:16:44 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/08 11:16:04 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_execute_builtin_directly(t_cmd *current, t_ms *ms)
{
	if (ft_strncmp(current->cmd, "cd", 3) == 0)
	{
 	   printf("Entered ft_cd_directly\n");
		ms->exit_status = ft_cd_directly(current, ms);
	}
//	else if (ft_strncmp(current->cmd, "echo", 5) == 0)
//		ms->exit_status = ft_echo_nonfork(current->arg);
	else if (ft_strncmp(current->cmd, "env", 4) == 0)
	{
        printf("Entered ft_env_directly\n");
		ms->exit_status = ft_env_direct(environ);
	}
//	else if (ft_strncmp(current->cmd, "exit", 5) == 0)
//		ft_exit(ms);
//	else if (ft_strncmp(current->cmd, "export", 7) == 0)
//		ms->exit_status = ft_export_nonfork(current->arg, ms);
	else if (ft_strncmp(current->cmd, "pwd", 4) == 0)
	{
        printf("Entered ft_pwd_directly\n");
		ms->exit_status = ft_pwd_direct(current);
	}
//	else if (ft_strncmp(current->cmd, "unset", 6) == 0)
//		ms->exit_status = ft_unset_nonfork(current->arg, ms);
}

void	ft_execute_forked_builtin(t_cmd *current, t_ms *ms)
{
	if (ft_strncmp(current->cmd, "cd", 3) == 0)
	{
	    printf("Entered ft_cd_as_forked\n");
		ft_cd_as_forked(current, ms);
	}
//	else if (ft_strncmp(current->cmd, "echo", 5) == 0)
//		ft_echo_fork(current->arg, ms);
	else if (ft_strncmp(current->cmd, "env", 4) == 0)
	{
        printf("Entered ft_env_forked\n");
		ft_env_forked(ms);
	}
//	else if (ft_strncmp(current->cmd, "exit", 5) == 0)
//	{
//		ft_exit(ms);
//		exit(1);
//	}
//	else if (ft_strncmp(current->cmd, "export", 7) == 0)
//		ft_export_fork(current->arg, ms);
//	else if (ft_strncmp(current->cmd, "pwd", 4) == 0)
	else if (ft_strncmp(current->cmd, "pwd", 4) == 0)
	{
        printf("Entered ft_pwd_as_forked\n");
		ft_pwd_forked(current, ms);
	}
//	else if (ft_strncmp(current->cmd, "unset", 6) == 0)
//		ft_unset_fork(current->arg, ms);
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