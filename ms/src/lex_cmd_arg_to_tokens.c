/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cmd_arg_to_tokens.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:51:20 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/15 09:16:53 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Take an array of string tokens (command line) 
and count the number of commands in them
(separated by pipe symbol) Return the number of commands */
int	count_cmd(char **tokens)
{
	int	i;
	int	total_cmds;

	i = 0;
	total_cmds = 0;
	if (tokens == NULL)
		return (total_cmds);
	while (tokens[i])
	{
		total_cmds++;
		while (tokens[i] && ft_strncmp(tokens[i], "|", 2) != 0)
			i++;
		if (tokens[i] && ft_strncmp(tokens[i], "|", 2) == 0)
			i++;
	}
	return (total_cmds);
}

/* Allocate memory for a new command node.
Create a new node and store the copy of the
content in it */
t_cmd	*create_new_cmd_node(char **tokens, int *i, int total_arg)
{
	int		j;
	char	**arg;
	t_cmd	*new_node;

	arg = (char **)malloc(sizeof(char *) * (total_arg + 1));
	j = 0;
	while (tokens[*i] && ft_strncmp(tokens[*i], "|", 2) != 0)
	{
		arg[j] = ft_strdup(tokens[*i]);
		(*i)++;
		j++;
	}
	arg[j] = NULL;
	new_node = allocate_and_initialize_cmd();
	new_node->cmd = ft_strdup(arg[0]);
	new_node->arg = arg;
	new_node->next = NULL;
	return (new_node);
}

/* Count how many arguments (strings)
are there for a single command until it 
reaches either the end of the list or a pipe */
int	count_arg(char **tokens, int i)
{
	int	j;
	int	total_arg;

	total_arg = 0;
	j = i;
	while (tokens[j] && ft_strncmp(tokens[j], "|", 2) != 0)
	{
		total_arg++;
		j++;
	}
	return (total_arg);
}

/* Transform the input string, so that the spaces are replaced with the token
delimiter to make the input string easier to parse. If it encounters ", ', or {,
it looks for the corresponding closing delimiter and skips everything in between.
*/
char	*ft_transform_for_lexer(const char *in_str)
{
	int		i;
	char	*out_str;
	char	closing_delimiter;

	i = 0;
	out_str = ft_strdup(in_str);
	if (!out_str)
		return (NULL);
	while (out_str[i] != '\0')
	{
		if (out_str[i] == ' ')
			out_str[i] = 29;
		else if (out_str[i] == '"' || out_str[i] == '\'' || out_str[i] == '{')
		{
			if (out_str[i] == '{')
				closing_delimiter = '}';
			else
				closing_delimiter = out_str[i];
			i++;
			while (out_str[i] != closing_delimiter)
				i++;
		}
		i++;
	}
	return (out_str);
}
