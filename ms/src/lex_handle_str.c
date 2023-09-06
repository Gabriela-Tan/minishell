/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handle_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/05 15:56:38 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	out_str = strdup(in_str);
	if (!out_str)
		return (NULL);
	while (out_str[i] != '\0')
	{
		if (out_str[i] == ' ')
			out_str[i] = TOKEN_DELIMITER;
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

/* Process array of string tokens by iterating through each token.
Check if the token starts with " or '. 
If so, trim surrounding quotes and update the token in the array. 
Return updated array with removed surrounding quotes. */
char	**ft_handle_quotes(char **tokens)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '"')
		{
			trimmed = ft_strtrim(tokens[i], "\"");
			tokens[i] = trimmed;
		}
		else if (tokens[i][0] == '\'')
		{
			trimmed = ft_strtrim(tokens[i], "'");
			tokens[i] = trimmed;
		}
		i++;
	}
	return (tokens);
}

/* Prepare the input by marking spaces outside of quotes and braces.
Process strings within quotes. Further process the parsed words with lexer.
*/
void	ft_parse_input_string(const char *in_str, t_env *env)
{
	char	**tokens;

	tokens = ft_split(ft_transform_for_lexer(in_str), TOKEN_DELIMITER);
	tokens = ft_handle_quotes(tokens);
	env->tokens = tokens;
}
