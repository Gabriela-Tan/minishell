/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_helpers2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 23:15:47 by mvocasko          #+#    #+#             */
/*   Updated: 2023/10/22 00:11:35 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//allocates memory for export variables and values 
//from the current command arguments

void	mem_variables(t_cmd *current, char ***variables, char ***values)
{
	int	i;

	i = 1;
	while (current->arg[i] != NULL)
	{
		ft_realloc(variables, i * sizeof(char *));
		ft_realloc(values, i * sizeof(char *));
		if (*variables == NULL || *values == NULL)
		{
			printf("export: failed to allocate memory.\n");
			exit (1);
		}
		i++;
	}
	(*variables)[i - 1] = NULL;
	(*values)[i - 1] = NULL;
}

// Function to parse variable names and values

void	parse_var_values(t_cmd *current, char ***variables, char ***values)
{
	int		i;
	char	*var_name;
	char	*equal_sign;
	char	*var_value;

	i = 1;
	while (current->arg[i] != NULL)
	{
		var_name = current->arg[i];
		equal_sign = ft_strchr(var_name, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			var_value = equal_sign + 1;
			(*variables)[i - 1] = ft_strdup(var_name);
			(*values)[i - 1] = ft_strdup(var_value);
		}
		i++;
	}
}

//ask norminette, just BS 
void	parse_export_args(t_cmd *current, char ***variables, char ***values)
{
	mem_variables(current, variables, values);
	parse_var_values(current, variables, values);
}
