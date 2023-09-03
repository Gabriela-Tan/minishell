/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cmd_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:51:20 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/03 11:20:52 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Counts the number of individual commands in the tokens array, which
makes up the entire command line input. Commands are separated by pipe. */
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

/* Iterate over the array of tokens, build a linked list (t_cmd)
where each node represents a command and its arguments,
all stored in the env structure under env->cmd_head */
void	cmd_to_tokens(char **tokens, t_env *env)
{
	int		i;
	int		j;
	t_cmd	*last;
	
	i = 0;
	last = NULL;
	while (tokens[i])
	{
		t_cmd *new_node = create_new_node(&i, tokens);
		if (env->cmd_head == NULL)
		{
			env->cmd_head = new_node;
			last = new_node;
		}
		else
		{
			last->next = new_node;
			last = new_node;
		}
		if (tokens[i] && ft_strncmp(tokens[i], "|", 2) == 0)
			i++;
	}
}

/* It creates a new t_cmd node, populates it
with the command name and arguments, and returns it. */
t_cmd	*create_new_node(int *i, char **tokens)
{
	int		j;
	t_cmd	*new_node;
	char	**arg;
	int		total_arg;
	
	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	new_node->cmd = ft_strdup(tokens[*i]);
	(*i)++;
	j = 0;
	total_arg = count_arg(tokens, *i);
	arg = (char **)malloc(sizeof(char *) * (total_arg + 1));
	while (tokens[*i] && ft_strncmp(tokens[*i], "|", 2) != 0)
		arg[j++] = ft_strdup(tokens[(*i)++]);
	arg[j] = NULL;
	new_node->arg = arg;
	new_node->next = NULL;
	return new_node;
}

/////////////////////////////////////////////////////////////////

/* Count arguments, start by skipping the command itself, then 
Count until hitting a pipe symbol or end of array */
int	count_arg(char **tokens, int i)
{
	int	total_arg = 0;

	if (tokens[i])
		i++;
	while (tokens[i] && ft_strncmp(tokens[i], "|", 2) != 0)
	{
		total_arg++;
		i++;
	}
	return (total_arg);
}

/* Add a new command to the linked list */
void	add_cmd(t_cmd **head, char *cmd, char **arg)
{
	t_cmd	*new_node;
	t_cmd	*last;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	last = *head;
	new_node->cmd = ft_strdup(cmd);
	new_node->arg = arg;
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new_node;
}

/* Tokenize commands and arguments */
void	tokenize_cmd_and_args(char **tokens, t_env *env)
{
	int		i;
	int		j;
	char	**arg;
	t_cmd	*head;

	head = NULL;
	i = 0;
	while (tokens[i])
	{
		j = 0;
		int total_arg = count_arg(tokens, i);
		arg = (char **)malloc(sizeof(char *) * (total_arg + 1));
		while (tokens[i] != NULL && ft_strncmp(tokens[i], "|", 2) != 0)
		{
			arg[j++] = ft_strdup(tokens[i]);
			i++;
		}
		arg[j] = NULL;
		add_cmd(&head, arg[0], arg);
		if (tokens[i] != NULL)
			i++;
	}
	env->cmd_head = head;
}