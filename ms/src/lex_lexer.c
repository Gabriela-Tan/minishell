/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/03 11:39:40 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(char **tokens, t_env *env)
{
	process_redirs(tokens, env);
	cmd_to_tokens(tokens, env);
	tokenize_cmd_and_args(char **tokens, t_env *env);

//ft_command_check
	free_array(tokens);
}
