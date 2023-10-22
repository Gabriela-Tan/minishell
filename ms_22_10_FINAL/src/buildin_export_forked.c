/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export_forked.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:26:00 by mvocasko          #+#    #+#             */
/*   Updated: 2023/10/22 00:11:46 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//updates env var by replacing its value with a new value
//if env_var contains '=' it creates a new env var
//with the same name but the updated value

char	*update_single_env_var(const char *env_var, const char *new_value)
{
	char	*updated_env;
	char	*equal_sign;

	updated_env = NULL;
	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign != NULL)
	{
		*equal_sign = '\0';
		updated_env = ft_strjoin(env_var, "=");
		updated_env = ft_strjoin(updated_env, new_value);
	}
	return (updated_env);
}

//updates the environment variable with the new value

void	update_env_variables(char **variables, char **values)
{
	int		i;
	int		j;
	char	*updated_env_var;

	i = 0;
	while (variables[i] != NULL)
	{
		j = 0;
		while (environ[j] != NULL)
		{
			updated_env_var = update_single_env_var(environ[j], values[i]);
			if (updated_env_var != NULL)
			{
				environ[j] = updated_env_var;
				break ;
			}
			j++;
		}
		i++;
	}
}

// Function to print declared variables

void	print_declared_variabless(char **variables)
{
	int		i;
	char	*env_var;

	i = 0;
	while (variables[i] != NULL)
	{
		env_var = getenv(variables[i]);
		if (env_var != NULL)
			printf("declare -x %s=\"%s\"\n", variables[i], env_var);
		i++;
	}
}

//function to call the two divided functions 
//just for norminette related bs 

void	update_and_print_exported_variables(char **variables, char **values)
{
	update_env_variables(variables, values);
	print_declared_variabless(variables);
}

//responsible for exporting forked variables

void	ft_export_forked(t_cmd *current, t_ms *ms)
{
	char	**variables;
	char	**values;

	variables = NULL;
	values = NULL;
	parse_export_args(current, &variables, &values);
	update_and_print_exported_variables(variables, values);
	free_and_exit(0, ms);
}
