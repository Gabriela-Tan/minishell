/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:37:26 by mvocasko          #+#    #+#             */
/*   Updated: 2023/10/21 00:39:50 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//to search and remove a specific env var (defined by prefix) 
//from an array of environment variables 
int	remove_from_environ(char **environ, char *prefix)
{
	int	k;
	int	j;

	k = 0;
	while (environ[k])
	{
		if (strncmp(prefix, environ[k], ft_strlen(prefix)) == 0)
		{
			j = k;
			while (environ[j] != NULL)
			{
				environ[j] = environ[j + 1];
				j++;
			}
			return (1);
		}
		k++;
	}
	return (0);
}
//responsible for unsetting env var based on the provided arg array
//it constructs a prefix for each variable,
//if var found in the environment (environ), it is removed

int	ft_unset_directly(char **arg)
{
	int		i;
	char	*prefix;
	int		found;

	i = 1;
	if (!arg[i])
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	while (arg[i])
	{
		prefix = ft_strjoin(arg[i], "=");
		found = remove_from_environ(environ, prefix);
		free(prefix);
		if (!found)
		{
			printf("unset: %s: not found in environment\n", arg[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
//function searches custom environment for variable (defined by prefix) 
//if found, removes it from the environment array

int	remove_from_custom_env(char **custom_env, char *prefix)
{
	int	k;
	int	j;

	k = 0;
	while (custom_env[k])
	{
		if (ft_strncmp(prefix, custom_env[k], ft_strlen(prefix)) == 0)
		{
			j = k;
			while (custom_env[j] != NULL)
			{
				custom_env[j] = custom_env[j + 1];
				j++;
			}
			return (1);
		}
		k++;
	}
	return (0);
}

int	ft_unset_as_forked(t_ms *ms, char **arg)
{
	int		i;
	char	*prefix;
	int		found;

	i = 1;
	if (!arg[i])
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	while (arg[i])
	{
		prefix = ft_strjoin(arg[i], "=");
		found = remove_from_custom_env(ms->env, prefix);
		free(prefix);
		if (!found)
		{
			printf("unset: %s: not found in environment\n", arg[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
