/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/29 17:00:16 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Processes input redirections like '<' and '<<' from a list of tokens.
Updates the ms to store the file or delimiter for the redirection.
last_ll (last fd for less-less operator) is a pointer to store the file
for '<<' redirection. last_l (last fd for less operator) is a pointer to store 
the file for '<' redirection. */
void	input_redirs(char **tokens, t_ms *ms, char **last_ll, char **last_l)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "<<", 3) == 0 && tokens[i + 1])
		{
			*last_ll = tokens[i + 1];
			ms->delim = ft_strdup(*last_ll);
		}
		else if (ft_strncmp(tokens[i], "<", 2) == 0 && tokens[i + 1])
		{
			*last_l = tokens[i + 1];
			ms->in_fd = open(*last_l, (O_RDONLY | O_CLOEXEC), 0777);
		}
		i++;
	}
}

/* Processes output redirections like '>' and '>>' from a list of tokens.
 Updates ms to store the file for the redirection. last_gg (last fd for
 greater-greater operator) is a pointer to store the file for '>>' redirection.
 last_g (last fd for greater operator) is a pointer to store the file for '>'
 */
void	output_redirs(char **tokens, t_ms *ms, char **last_gg, char **last_g)
{
	int		fd;
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], ">>", 3) == 0 && tokens[i + 1])
		{
			*last_gg = tokens[i + 1];
			fd = open(*last_gg, (O_WRONLY | O_CREAT | O_APPEND | O_CLOEXEC), 0777);
			if (ms->out_fd && ms->out_fd != fd)
				close(ms->out_fd);
			ms->out_fd = fd;
		}
		else if (ft_strncmp(tokens[i], ">", 2) == 0 && tokens[i + 1])
		{
			*last_g = tokens[i + 1];
			fd = open(*last_g, (O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC), 0777);
			if (ms->out_fd && ms->out_fd != fd)
				close(ms->out_fd);
			ms->out_fd = fd;
		}
		i++;
	}
}

/* Checks if a token is not a redirection operator.
Return 1 if the token is not a redirection, 0 otherwise. */
int	is_not_redir(char *tokens)
{
	if ((ft_strncmp(tokens, "<", 2) != 0)
		&& (ft_strncmp(tokens, ">", 2) != 0)
		&& (ft_strncmp(tokens, "<<", 3) != 0)
		&& (ft_strncmp(tokens, ">>", 3) != 0))
		return (1);
	return (0);
}

/* Creates a new array of tokens without any redirection operators. */
char	**array_wo_redirs(char **old_array, int *count, int i, int j)
{
	char	**new_array;

	while (old_array[++i] != NULL)
	{
		if (is_not_redir(old_array[i]) == 1)
			(*count)++;
		else
			i++;
	}
	new_array = (char **)malloc(sizeof(char *) * (*count + 1));
	i = -1;
	while (old_array[++i] != NULL)
	{
		if (is_not_redir(old_array[i]) == 1)
		{
			new_array[j] = ft_strdup(old_array[i]);
			j++;
		}
		else
			i++;
	}
	new_array[j] = NULL;
	return (new_array);
}

/* Integrate input_redirs and output_redirs to process all redirections. 
Remove redirection tokens from the token array and returns a new array. */
void	process_redirs(char **tokens, t_ms *ms)
{
	int		count;
	char	*last_gg;
	char	*last_g;
	char	*last_ll;
	char	*last_l;

	last_gg = NULL;
	last_g = NULL;
	last_ll = NULL;
	last_l = NULL;
	count = 0;
	output_redirs(tokens, ms, &last_gg, &last_g);
	input_redirs(tokens, ms, &last_ll, &last_l);
	tokens = array_wo_redirs(tokens, &count, -1, 0);
}

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