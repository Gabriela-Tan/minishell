/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/08 10:52:57 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Checks if a token is not a redirection operator.
Return 1 if the token is not a redirection, 0 otherwise. */
int	ft_is_not_redir(char *tokens)
{
	if ((ft_strncmp(tokens, "<", 2) != 0)
		&& (ft_strncmp(tokens, ">", 2) != 0)
		&& (ft_strncmp(tokens, "<<", 3) != 0)
		&& (ft_strncmp(tokens, ">>", 3) != 0))
		return (1);
	return (0);
}

/* Creates a new array without redirection symbols. 
Iterate through old array skip redirection targets.
Allocate memory for new array. If token is not a redirection,
copy is to new array. Otherwise, skip redirection target.
Add null terminator and return the new array. */
char	**ft_array_wo_redirs(char **old_array, int *count, int i, int j)
{
	char	**new_array;

	while (old_array[++i] != NULL)
	{
		if (ft_is_not_redir(old_array[i]) == 1)
			(*count)++;
		else
			i++;
	}
	new_array = (char **)malloc(sizeof(char *) * (*count + 1));
	i = -1;
	while (old_array[++i] != NULL)
	{
		if (ft_is_not_redir(old_array[i]) == 1)
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

/* Iterate through the array of tokens. Check if there is a token
after the current one. Check redirection type and update it in the 
current_cmd. If redirection is processed, skip it and its target.
Move to the next token. */
void	ft_process_redirs(t_cmd *current_cmd, char **tokens, int i)
{
	while (tokens[i])
	{
		if (tokens[i + 1])
		{
			if (ft_strncmp(tokens[i], "<<", 3) == 0)
				current_cmd->here_doc = ft_strdup(tokens[i + 1]);
			else if (ft_strncmp(tokens[i], "<", 2) == 0)
				current_cmd->input_redir = ft_strdup(tokens[i + 1]);
			else if (ft_strncmp(tokens[i], ">>", 3) == 0)
				current_cmd->append_output_redir = ft_strdup(tokens[i + 1]);
			else if (ft_strncmp(tokens[i], ">", 2) == 0)
				current_cmd->output_redir = ft_strdup(tokens[i + 1]);
			if (ft_strncmp(tokens[i], "<<", 3) == 0
				|| ft_strncmp(tokens[i], "<", 2) == 0
				|| ft_strncmp(tokens[i], ">>", 3) == 0
				|| ft_strncmp(tokens[i], ">", 2) == 0)
			{
				i += 2;
				continue ;
			}
		}
		i++;
	}
}
