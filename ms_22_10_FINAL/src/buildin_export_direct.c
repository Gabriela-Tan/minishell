/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export_direct.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:20:58 by mvocasko          #+#    #+#             */
/*   Updated: 2023/10/21 23:14:08 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
//calculates the length required for an env var string
//constructs the env var string by copying var_name, 
//adding an equal sign, and appending var_value

char	*create_env_var_str(char *var_name, char *var_value)
{
	int		env_var_len;
	char	*env_var_str;

	env_var_len = ft_strlen(var_name) + 1 + ft_strlen(var_value) + 1;
	env_var_str = malloc(env_var_len);
	if (env_var_str == NULL)
	{
		printf("export: failed to allocate memory.\n");
		return (NULL);
	}
	ft_strcpy(env_var_str, var_name);
	ft_strcat(env_var_str, "=");
	ft_strcat(env_var_str, var_value);
	return (env_var_str);
}

//iterates through the env variables, if it finds one with 
//matching var_name, updates it and assigns it to environment

int	add_env_var(char *var_name, char *var_value)
{
	int		j;
	char	**temp;

	j = 0;
	while (environ[j] != NULL)
	{
		if (strncmp(environ[j], var_name, strlen(var_name)) == 0)
		{
			environ[j] = create_env_var_str(var_name, var_value);
			if (environ[j] == NULL)
				return (1);
			else
				return (0);
		}
		j++;
	}
	temp = environ;
	ft_realloc(&temp, (j + 2) * sizeof(char *));
	if (temp == NULL)
		return (1);
	environ = temp;
	environ[j] = create_env_var_str(var_name, var_value);
	environ[j + 1] = NULL;
	return (0);
}

//first creates a new environment variable string
//then, it updates or adds the variable 

int	update_env_var(char *var_name, char *var_value)
{
	char	*env_var_str;
	int		status;

	env_var_str = create_env_var_str(var_name, var_value);
	if (env_var_str != NULL)
	{
		status = add_env_var(var_name, var_value);
		if (status != 0)
			free(env_var_str);
	}
	return (0);
}

// only handles the printing of environment variables

void	print_env_var(char *var_name)
{
	char	*env_var;

	env_var = getenv(var_name);
	if (env_var != NULL)
		printf("declare -x %s=\"%s\"\n", var_name, env_var);
}

//processes export command by iterating through the arguments
//for each argument, it checks if it contains an equal sign,
//it calls print_env_var to display the environment variable

int	ft_export_direct(t_cmd *current)
{
	int		i;
	int		status;
	char	*var_name;
	char	*equal_sign;
	char	*var_value;

	i = 1;
	status = 0;
	while (current->arg[i] != NULL)
	{
		var_name = current->arg[i];
		equal_sign = ft_strchr(var_name, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			var_value = equal_sign + 1;
			status = update_env_var(var_name, var_value);
		}
		else
			print_env_var(var_name);
		i++;
	}
	return (status);
}
