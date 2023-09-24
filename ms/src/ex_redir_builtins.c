/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redir_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:16:44 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/24 12:17:32 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Handle here document redirection by creating a pipe to pass
info from one process to another. Put the read and write fd into
the fd array. Then, if the pid is 0, the child process will read
from the fd[0] and write to the fd[1]. If the pid is not 0, the
parent will read from the fd[1] and write to the fd[0]. The
child process will exit after reading the delimiter. */
void	ft_heredoc(char *delim, int pid)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return ;
	if (pid == 0)
	{
		close(fd[0]);
		line = "";
		while (ft_strncmp(line, delim, ft_strlen(delim)) != 0)
		{
			line = readline("heredoc> ");
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
		}
		exit(0);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		wait(NULL);
	}
}

void	ft_error(void)
{
	perror("fork");
	exit(1);
}

void	ft_execute_builtin_directly(t_cmd *current, t_ms *ms)
{
	if (ft_strncmp(current->cmd, "cd", 3) == 0)
		ms->exit_status = ft_cd_directly(current, ms);
//	else if (ft_strncmp(current->cmd, "echo", 5) == 0)
//		ms->exit_status = ft_echo_nonfork(current->arg);
//	else if (ft_strncmp(current->cmd, "env", 4) == 0)
//		ms->exit_status = ft_env_nonfork();
//	else if (ft_strncmp(current->cmd, "exit", 5) == 0)
//		ft_exit(ms);
//	else if (ft_strncmp(current->cmd, "export", 7) == 0)
//		ms->exit_status = ft_export_nonfork(current->arg, ms);
//	else if (ft_strncmp(current->cmd, "pwd", 4) == 0)
//		ms->exit_status = ft_pwd_nonfork(current->arg);
//	else if (ft_strncmp(current->cmd, "unset", 6) == 0)
//		ms->exit_status = ft_unset_nonfork(current->arg, ms);
}

void	ft_execute_forked_builtin(t_cmd *current, t_ms *ms)
{
	if (ft_strncmp(current->cmd, "cd", 3) == 0)
		ft_cd_as_forked(current, ms);
//	else if (ft_strncmp(current->cmd, "echo", 5) == 0)
//		ft_echo_fork(current->arg, ms);
//	else if (ft_strncmp(current->cmd, "env", 4) == 0)
//		ft_env_fork(ms);
//	else if (ft_strncmp(current->cmd, "exit", 5) == 0)
//	{
//		ft_exit(ms);
//		exit(1);
//	}
//	else if (ft_strncmp(current->cmd, "export", 7) == 0)
//		ft_export_fork(current->arg, ms);
//	else if (ft_strncmp(current->cmd, "pwd", 4) == 0)
//		ft_pwd_fork(current->arg, ms);
//	else if (ft_strncmp(current->cmd, "unset", 6) == 0)
//		ft_unset_fork(current->arg, ms);
}

