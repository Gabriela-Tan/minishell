/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:04:12 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/15 17:19:38 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Loop through the linked list and count the number
of command nodes in it. Return the count */
int	ft_get_command_count(t_cmd *cmd_head)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_head;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/* Print an error message and exit the program with
status 127 (command not found) */
void	ft_command_not_found(t_cmd *current)
{
	write(2, "Command not found: ", 19);
	write(2, current->cmd, ft_strlen(current->cmd));
	write(2, "\n", 1);
	exit(127);
}

/* Handle the case where Ctrl+C is pressed to interrupt.
Replace line with empty string. Move the cursor to a
new line. Display the prompt again. */
void	ft_sigint(int received_signal)
{
	if (received_signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_redisplay();
	}
}
