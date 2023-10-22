/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:06:35 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/08 09:05:14 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Initialize the state for processing commands */
void	ft_init(t_ms *ms)
{
	ms->cmd_head = NULL;
	ms->i_last_cmd = -1;
	ms->in_fd = -1;
	ms->out_fd = -1;
	ms->delim = NULL;
	ms->saved_stdin = -1;
	ms->saved_stdout = -1;
	ms->exit_status = 0;
	ms->tokens = NULL;
	ms->env = ft_copy_environ();
	environ = ms->env;
	ft_change_prompt(ms);
}

/* Reset the state for processing commands changed
during the command execution */
void	ft_reset(t_ms *ms)
{
	ms->cmd_head = NULL;
	ms->i_last_cmd = -1;
	ms->delim = NULL;
	ms->in_fd = -1;
	ms->out_fd = -1;
	ms->saved_stdin = -1;
	ms->saved_stdout = -1;
	ms->tokens = NULL;
}

/* Allocate and initialize memory for the
cmd structure */
t_cmd	*allocate_and_initialize_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *) malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->arg = NULL;
	new_cmd->input_redir = NULL;
	new_cmd->output_redir = NULL;
	new_cmd->here_doc = NULL;
	new_cmd->append_output_redir = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
