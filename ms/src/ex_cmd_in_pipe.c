/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd_in_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/16 12:03:31 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Handle child process execution after forking.
Close read end of piple in child process. Redirect
stdout to write end of pipe. Close write end of pipe.
Check built-in and execute it, or execute it with
execve. If execve fails, print error message. Terminate
the child process. */
void	ft_handle_child_process(t_cmd *current, int fd[], t_ms *ms)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (ft_check_builtin(current->cmd))
		ft_execute_forked_builtin(current, ms);
	else if (execve(current->cmd, current->arg, environ) == -1)
		ft_command_not_found(current);
	exit(0);
}

/* Handle parent process execution after forking. Close
write end of pipe in the parent process. Redirect stdin
to read end of pipe. Close read end of pipe. Wait for
child process to terminate, get its exit status. */
void	ft_handle_parent_process(int fd[], pid_t pid, t_ms *ms)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, &ms->exit_status, 0);
}

/* Handles execution of commands that are piped together.
Declare two fds for the pipe. Declare a pid for the forking.
Loop through the linked list of commands. Fork the process and
store the pid. If the pid is 0, run the handle_child_process.*/
void	ft_execute_cmd_in_pipe(t_ms *ms, t_cmd *current)
{
	int		fd[2];
	pid_t	pid;

	while (current->next)
	{
		if (pipe(fd) == -1)
			ft_error();
		pid = fork();
		if (pid == -1)
			ft_error();

		if (pid == 0)
			ft_handle_child_process(current, fd, ms);
		else
			ft_handle_parent_process(fd, pid, ms);

		current = current->next;
	}
}
