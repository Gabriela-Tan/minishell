/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_replace_symbols.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:20:50 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/17 11:36:35 by gabriela         ###   ########.fr       */
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

/* Traverse each command and its arguments in the linked list, replacing
special symbols with exit status and home directory */
void	ft_replace_symbols(t_ms *ms)
{
	t_cmd	*current;
	int		i;

	current = ms->cmd_head;
	while (current != NULL)
	{
		if (ft_strchr(current->cmd, '$'))
			current->cmd = ft_replace_exit(current->cmd, ms->exit_status, 0, 0);
		else if (ft_strchr(current->cmd, '~'))
			current->cmd = ft_replace_home_path
				(current->cmd, 0, getenv("HOME"));
		i = 0;
		while (current->arg && current->arg[i] != NULL)
		{
			if (ft_strchr(current->arg[i], '$'))
				current->arg[i] = ft_replace_exit
					(current->arg[i], ms->exit_status, 0, 0);
			else if (ft_strchr(current->arg[i], '~'))
				current->arg[i] = ft_replace_home_path
					(current->arg[i], 0, getenv("HOME"));
			i++;
		}
		current = current->next;
	}
}

/* Replace  $? with exit status and return the updated token */
char	*ft_replace_exit(char *token, int exit_status, int i, int replaced)
{
	char	*exit_str;
	char	*new_str;
	char	*temp;

	while (token[i] != '\0')
	{
		if (replaced == 0 && token[i] == '$' && token[i + 1] == '?')
		{
			exit_str = ft_itoa(exit_status >> 8);
			new_str = ft_substr(token, 0, i);
			temp = ft_strjoin(new_str, exit_str);
			free(new_str);
			free(exit_str);
			new_str = ft_strjoin(temp, token + i + 2);
			free(temp);
			free(token);
			token = new_str;
			replaced = 1;
			i = 0;
		}
		i++;
	}
	return (token);
}

/* Replaces ~ according to the character that follows it.
If it is followed by a /, the tilde is replaced with home_path.
If it is the last character, entire token is replaced with home_path.*/
char	*ft_replace_home_path(char *token, int i, char *home_path)
{
	char	*trimmed;
	char	*temp;

	while (token[i] != '\0')
	{
		if (token[i] == '~')
		{
			if (token[i + 1] == '/')
			{
				trimmed = ft_strtrim(token, "~");
				temp = ft_strjoin(home_path, trimmed);
				free(trimmed);
				free(token);
				return (temp);
			}
			else if (token[i + 1] == '\0')
			{
				free(token);
				return (ft_strdup(home_path));
			}
			break ;
		}
		i++;
	}
	return (token);
}
