/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_handle_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/08/31 14:18:50 by gabriela         ###   ########.fr       */
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
	UNUSED(env);
	char	**tokens;

	tokens = ft_split(ft_transform_for_lexer(in_str), TOKEN_DELIMITER);
	tokens = ft_handle_quotes(tokens);
//	ft_test_lexer(tokens, env);
}

/*
// Placeholder for ft_lexer
void	ft_test_lexer(char **tokens, t_env *env)
{
	UNUSED(env);

	printf("Tokens received by lexer:\n");
	int i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}

// Test for ft_parse_input_string
void test_parse_input_string(const char *input)
{
	t_env env = {0};
	printf("Testing with input: %s\n", input);
	ft_parse_input_string(input, &env);
	printf("\n");
}

// Test for ft_handle_quotes
void test_handle_quotes(char **tokens)
{
	printf("Before handling quotes:\n");
	int i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
	tokens = ft_handle_quotes(tokens);
	printf("After handling quotes:\n");
	i = 0;
	while (tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}

int main(void)
{
	// Tests for ft_parse_input_string
	test_parse_input_string("echo \"Hello World\"");
	test_parse_input_string("ls -la 'my dir'");
	test_parse_input_string("grep {pattern} file.txt");

	// Test cases for ft_handle_quotes
	printf("\nTesting ft_handle_quotes:\n");
	char *test_tokens1[] = {"echo", "\"Hello World\"", "'test'", NULL};
	test_handle_quotes(test_tokens1);

	char *test_tokens2[] = {"ls", "-la", "'my dir'", NULL};
	test_handle_quotes(test_tokens2);
}
*/