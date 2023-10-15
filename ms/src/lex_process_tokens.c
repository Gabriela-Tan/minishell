/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_process_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:42:29 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/08 10:45:59 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Continuation of ft_process_tokens. If the current token is a
redirection, skip it and its following token by += 2. Count the
number of arguments for the current command starting from index i. 
A new command node is created and its arguments are processed. */
void	ft_norm(char **tok_wo_red, char **tokens, int *i, t_cmd **new_node)
{
	int	total_arg;

	if (!ft_is_not_redir(tok_wo_red[*i]))
	{
		*i += 2;
		return ;
	}
	total_arg = count_arg(tok_wo_red, *i);
	*new_node = create_new_cmd_node(tok_wo_red, i, total_arg);
	ft_process_redirs(*new_node, tokens, 0);
}

/* Iterate through the tokens without redirection symbols starting
from index i. Update linked list of commands. If it's the first
command, set ms->cmd_head to the new node. Else, append the new node
to the end of the list and update last. If there is a pipe, skip it. */
void	ft_process_tokens(char **tok_wo_red, char **tokens, t_ms *ms, int i)
{
	t_cmd	*new_node;
	t_cmd	*last;

	last = NULL;
	while (tok_wo_red[i])
	{
		ft_norm(tok_wo_red, tokens, &i, &new_node);
		if (new_node == NULL)
			continue ;
		if (ms->cmd_head == NULL)
		{
			ms->cmd_head = new_node;
			last = new_node;
		}
		else
		{
			last->next = new_node;
			last = new_node;
		}
		if (tok_wo_red[i] && ft_strncmp(tok_wo_red[i], "|", 2) == 0)
			i++;
	}
}

/* Tokenize the command line input into individual parts. 
Count stores the number of tokend in tokens without redirection
symbols. Index to traverse through ft_process_tokens. I and J are indexes
for ft_array_wo_redirs. */
void	ft_tokenize_cmd_and_args(char **tokens, t_ms *ms)
{
	int		index;
	char	**tok_wo_red;
	int		count;
	int		i;
	int		j;

	index = 0;
	i = -1;
	j = 0;
	tok_wo_red = ft_array_wo_redirs(tokens, &count, i, j);
	ft_process_tokens(tok_wo_red, tokens, ms, index);
	free_array(tok_wo_red);
}
