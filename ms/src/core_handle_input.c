/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_handle_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/10 09:34:22 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handle_input(char *input, t_ms *ms, char *prompt)
{
	if (!input)
	{
		printf("exit\n");
		free(prompt);
		exit(0);
	}
	else if (input[0] != '\0')
	{
		free(prompt);
		add_history(input);
		ft_reset(ms);
		ft_parse_input_string(input, ms);
		ms->i_last_cmd = ft_get_command_count(ms->cmd_head) - 1;
//		if (ms->i_last_cmd >= 0)
//			ft_executor(ms);
	}
}

void	ft_lexer(char **tokens, t_ms *ms)
{
	process_redirs(tokens, ms);
	tokenize_cmd_and_args(tokens, ms);
	ft_check_cmd_type(ms);
	free_array(tokens);
}

/* Prepare the input by marking spaces outside of quotes and braces.
Process strings within quotes. Further process the parsed words with lexer.
*/
void	ft_parse_input_string(const char *in_str, t_ms *ms)
{
	char	**tokens;

	tokens = ft_split(ft_transform_for_lexer(in_str), TOKEN_DELIMITER);
	ft_handle_quoted_env_vars(ms);
	ft_handle_unquoted_env_vars(ms);
//handle status var
	ms->tokens = tokens;
	ft_lexer(tokens, ms);
}

//executor
