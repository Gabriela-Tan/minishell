/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/14 11:16:02 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* If prev_fd is not -1 (not piped), duplicate it to stdin for piping
the output of the previous command as input to the current cmd.
Set up input/output redirection. If there is builtin, execute it.
Else execute with execve or throw an error message. */
void	ft_child_process(int prev_fd, t_cmd *current, t_ms *ms)
{
	int	in_fd;
	int	out_fd;

	in_fd = -1;
	out_fd = -1;
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	ft_setup_input_redir(prev_fd, current, &in_fd);
	ft_setup_output_redir(current, ms, &out_fd);
	if (ft_check_builtin(current->cmd))
		ft_execute_forked_builtin(current, ms);
	if (execve(current->cmd, current->arg, environ) == -1)
		ft_command_not_found(current);
	exit(0);
}

/* Close the previous pipe if it exists. If there is next command,
set up the pipe for it. Close the write end of the current pipe.
Wait for the child process to finish and get its exit status. */
void	ft_parent_process(int *prev_fd, int pid, t_ms *ms, t_cmd *current)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (current->next)
		*prev_fd = ms->pipe_fd[0];
	close(ms->pipe_fd[1]);
	waitpid(pid, &ms->exit_status, 0);
}

/* Check if the current command is piped either to 
the next command or from the previous command. */
int	ft_check_if_piped(t_cmd *current, int prev_fd)
{
	int	is_piped;

	if ((current->next != NULL) || (prev_fd != -1))
		is_piped = 1;
	else
		is_piped = 0;
	return (is_piped);
}

/* Return 1 if the current command should be skipped, else 0 */
int	ft_skip_cmd(t_ms *ms, t_cmd *current, int *prev_fd, int is_redir)
{
	if (ft_handle_hd_bi(ms, current, prev_fd, is_redir))
	{
		if (*prev_fd != -1)
		{
			close(*prev_fd);
			*prev_fd = -1;
		}
		return (1);
	}
	return (0);
}

/* Loop through the list of commands and execute each one.
Check and handle heredoc and builtin commands.
Set up a pipe if there is a next command.
Fork the current process.
Execute the child process, execute the parent process.
Move to the next command in the list.
*/
void	ft_execute_cmd(t_ms *ms, t_cmd *current, int prev_fd)
{
	int	pid;
	int	is_redir;

	is_redir = (current->input_redir != NULL)
		|| (current->output_redir != NULL)
		|| (current->append_output_redir != NULL);
	while (current)
	{
		if (ft_skip_cmd(ms, current, &prev_fd, is_redir))
		{
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
