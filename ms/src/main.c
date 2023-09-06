/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 10:55:18 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/05 15:59:52 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_commands(t_cmd *head)
{
	t_cmd	*current;
	int		cmd_count;
	int		arg_count;

	current = head;
	cmd_count = 1;
	while (current != NULL)
	{
		printf("Command %d: %s\n", cmd_count, current->cmd);
		arg_count = 0;
		while (current->arg[arg_count])
		{
			printf("\tArg %d: %s\n", arg_count, current->arg[arg_count]);
			arg_count++;
		}
		current = current->next;
		cmd_count++;
	}
}

int	main(void)
{
	t_env	env;
	char	*input;
	char	*transformed_input;

	ft_init(&env);
	printf("Enter a command: ");
	input = readline(NULL);
	if (!input)
	{
		printf("Error: Failed to read line\n");
		return (1);
	}
	transformed_input = ft_transform_for_lexer(input);
	ft_parse_input_string(transformed_input, &env);
	ft_lexer(env.tokens, &env);
	print_commands(env.cmd_head);
	free(input);
	free(transformed_input);
	return (0);
}
