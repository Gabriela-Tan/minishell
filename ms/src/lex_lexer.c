/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/05 15:05:15 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lexer(char **tokens, t_env *env)
{
	process_redirs(tokens, env);
	tokenize_cmd_and_args(tokens, env);
	ft_check_cmd_type(env);
	free_array(tokens);
}
