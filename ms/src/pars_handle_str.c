/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_handle_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:13:58 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/10 09:21:12 by gabriela         ###   ########.fr       */
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

