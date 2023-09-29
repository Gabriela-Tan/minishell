/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/29 10:15:31 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/* If there is a pipe with a previous command, redirect its
output to the input of the current command. 
If there is a next command, redirect output of current cmd
to be input of next cmd. Else if its the last cmd in the
pipeline with output redirection, redirect its output to
out_fd. If the cmd is builtin, execute it with builtin,
or use execve if it's not builtin.
*/
void	ft_child_process(int prev_fd, t_cmd *current, t_ms *ms)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->next)
	{
		dup2(ms->pipe_fd[1], STDOUT_FILENO);
		close(ms->pipe_fd[1]);
	}
	else if (ms->out_fd != -1)
	{
		dup2(ms->out_fd, STDOUT_FILENO);
		close(ms->out_fd);
	}
	if (ft_check_builtin(current->cmd))
		ft_execute_forked_builtin(current, ms);
	else if (execve(current->cmd, current->arg, environ) == -1)
		ft_command_not_found(current);
	exit(0);
}

/* Close read end of previous pipe. If there is next cmd,
store read end of current pipe in prev_fd. If there is no
next command, close write end of current pipe.
Wait for child process to finish. */
void	ft_parent_process(int *prev_fd, int pid, t_ms *ms, t_cmd *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
		*prev_fd = ms->pipe_fd[0];
	close(ms->pipe_fd[1]);
	waitpid(pid, &ms->exit_status, 0);
}

/* Check if there is a pipe with previous command. */
int	ft_check_if_piped(t_cmd *current, int prev_fd)
{
	int	is_piped;

	if ((current->next != NULL) || (prev_fd != -1))
		is_piped = 1;
	else
		is_piped = 0;
	return (is_piped);
}

/* Execute commands in the list and handle the commands that are
piped together. Prev_fd keeps track of read end of the previous pipe
(initialized to -1 because there is no previous).
Loop through commands. Fork child process and handle it, then
handle the parent. If there is only one command, execute it directly.
*/
void	ft_execute_cmd(t_ms *ms, t_cmd *current)
{
	int		prev_fd;
	int		pid;
	int		is_piped;

	prev_fd = -1;
	while (current)
	{
		is_piped = ft_check_if_piped(current, prev_fd);
		if (!is_piped && ft_check_builtin(current->cmd))
		{
			ft_execute_builtin_directly(current, ms);
			current = current->next;
			continue ;
		}
		if (current->next && pipe(ms->pipe_fd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			ft_child_process(prev_fd, current, ms);
		else
			ft_parent_process(&prev_fd, pid, ms, current);
		current = current->next;
	}
}
