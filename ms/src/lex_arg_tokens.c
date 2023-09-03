/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_arg_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:55:18 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/03 11:21:50 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

/*
int main()
{
	// Sample tokens array
	char *sample_words[] = {"ls", "-l", "|", "grep", ".txt", NULL};

	t_env env;
	env.cmd_head = NULL;
	tokenize_cmd_and_args(sample_words, &env);
	t_cmd *temp = env.cmd_head;
	while (temp != NULL)
	{
		printf("Command: %s\n", temp->cmd);
		printf("Arguments: ");
		for (int i = 0; temp->arg[i] != NULL; i++)
		{
			printf("%s ", temp->arg[i]);
		}
		printf("\n");
		temp = temp->next;
	}
	return 0;
}
*/

