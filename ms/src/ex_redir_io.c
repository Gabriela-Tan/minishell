/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_redir_io.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 13:48:02 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/08 09:56:20 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* If there is a previous pipe (prev_fd != -1), duplicate the fd to
standard input an close the original fd. 
If input redirection is present, open the file file for reading and
duplicate its fd to standard input. Close the original fd. */
void	ft_setup_input_redir(int prev_fd, t_cmd *current, int *in_fd)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (current->input_redir)
	{
		*in_fd = open(current->input_redir, O_RDONLY | O_CLOEXEC, 0777);
		dup2(*in_fd, STDIN_FILENO);
		close(*in_fd);
	}
}

/* If there is a next command, set up a pipe for output. If output 
redirection is specified as > or >>, open/create or append the file
for writing and duplicate the fd to std. output. Close the original fd. */
void	ft_setup_output_redir(t_cmd *current, t_ms *ms, int *out_fd)
{
	if (current->next)
	{
		dup2(ms->pipe_fd[1], STDOUT_FILENO);
		close(ms->pipe_fd[1]);
	}
	else if (current->output_redir)
	{
		*out_fd = open(current->output_redir, O_WRONLY | O_CREAT
				| O_TRUNC | O_CLOEXEC, 0777);
		dup2(*out_fd, STDOUT_FILENO);
		close(*out_fd);
	}
	else if (current->append_output_redir)
	{
		*out_fd = open(current->append_output_redir, O_WRONLY | O_CREAT
				| O_APPEND | O_CLOEXEC, 0777);
		dup2(*out_fd, STDOUT_FILENO);
		close(*out_fd);
	}
}

/* If heredoc is specified, execute it, updating prev_fd to read
from the heredoc. If the command is a builtin and not part of a pipe,
execute it directly. If heredoc was used, close its fd. 
Return 0 if the command is not a builtin, 1 otherwise. */
int	ft_handle_heredoc_builtin(t_ms *ms, t_cmd *current, int *prev_fd)
{
	int	heredoc_fd[2];

	if (current->here_doc)
	{
		ft_heredoc(current->here_doc, heredoc_fd);
		*prev_fd = heredoc_fd[0];
		free(current->here_doc);
		current->here_doc = NULL;
	}
	if (!ft_check_if_piped(current, *prev_fd) && ft_check_builtin(current->cmd))
	{
		ft_execute_builtin_directly(current, ms);
		if (*prev_fd != -1)
		{
			close(*prev_fd);
			*prev_fd = -1;
		}
		return (1);
	}
	return (0);
}

/* Keep reading lines in a loop until the delimiter is reached. 
Write each line to the write end of the pipe. Close the pipe. */
void	ft_heredoc(char *delimiter, int heredoc_fd[2])
{
	char	*line;

	pipe(heredoc_fd);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = readline(NULL);
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_fd[1], line, strlen(line));
		write(heredoc_fd[1], "\n", 1);
		free(line);
	}
	close(heredoc_fd[1]);
}

/* Restore original standard input and output using dup2
and close the saved standard input an output file descriptors */
void	ft_restore_input_output(t_ms *ms)
{
	dup2(ms->saved_stdout, STDOUT_FILENO);
	dup2(ms->saved_stdin, STDIN_FILENO);
	close(ms->saved_stdin);
	close(ms->saved_stdout);
}
