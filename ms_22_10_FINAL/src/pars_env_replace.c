/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_env_replace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:20:55 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/22 00:18:41 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  Check quotes for each argument in the command. If quotes are found,
trim them and performs an environment variable replacement for double
quotes. Single quotes are used to preserve the literal value of each
character within the quotes, so variables and special characters do not
get expanded when they are enclosed in single quotes. */
int	*ft_handle_quotes(char **arg, int i, int arg_len)
{
	char	*trimmed;
	int		*skip_replacement_flags;

	trimmed = NULL;
	while (arg[arg_len])
		arg_len++;
	skip_replacement_flags = malloc(arg_len * sizeof(int));
	while (arg[i])
	{
		skip_replacement_flags[i] = 0;
		if (arg[i][0] == '"')
		{
			arg[i] = ft_replace_env_var(arg[i], 0, 0);
			trimmed = ft_strtrim(arg[i], "\"");
		}
		else if (arg[i][0] == '\'')
		{
			trimmed = ft_strtrim(arg[i], "'");
			skip_replacement_flags[i] = 1;
		}
		ft_free_trimmed(&arg[i], trimmed);
		trimmed = NULL;
		i++;
	}
	return (skip_replacement_flags);
}

/* Splitting above function because of stupid norminette */
void	ft_handle_quoted_env_vars(t_ms *ms)
{
	t_cmd	*current_cmd;
	int		*skip_replacement_flags;

	current_cmd = ms->cmd_head;
	while (current_cmd)
	{
		skip_replacement_flags = ft_handle_quotes(current_cmd->arg, 0, 0);
		ft_handle_unquoted_env_vars(current_cmd->arg, skip_replacement_flags);
		free(skip_replacement_flags);
		current_cmd = current_cmd->next;
	}
}

/* Preprocessing each command's argument to replace any environment
variables before the command is executed, while avoiding replacing
anything with quoted arguments.*/
void	ft_handle_unquoted_env_vars(char **arg, int *skip_replacement_flags)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i])
	{
		len = ft_strlen(arg[i]);
		if (!skip_replacement_flags[i])
		{
			if ((arg[i][0] != '\'' && arg[i][len - 1] != '\'') &&
				(arg[i][0] != '"' && arg[i][len - 1] != '"'))
			{
				arg[i] = ft_replace_env_var(arg[i], 0, 0);
			}
		}
		i++;
	}
}

/* Return the starting index of the next environment variable found
in token, while $ is found. If none is found, return -1. */
int	ft_find_next_env_var(char *token, int start, int *j)
{
	int	i;

	i = start;
	*j = 0;
	while (token[i] != '\0')
	{
		if (token[i] == '$')
		{
			while (ft_isalnum(token[i + 1 + *j])
				|| token[i + 1 + *j] == '_')
				(*j)++;
			if (*j != 0)
			{
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

/* Replace all occurencies of the environment variable found in
a given token, return the updated token with replaced env. var. */
char	*ft_replace_env_var(char *token, int i, int j)
{
	char	*env_var;
	char	*token_update;
	char	*new_str;

	i = ft_find_next_env_var(token, i, &j);
	while (i != -1)
	{
		token_update = ft_substr(token, i + 1, j);
		env_var = getenv(token_update);
		if (env_var == NULL)
			env_var = "";
		new_str = ft_substr(token, 0, i);
		token_update = ft_strjoin(new_str, env_var);
		free(new_str);
		new_str = ft_strjoin(token_update, token + i + j + 1);
		free(token_update);
		free(token);
		token = new_str;
		i = 0;
		j = 0;
		i = ft_find_next_env_var(token, i, &j);
	}
	return (token);
}
