/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:34:33 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/14 18:15:54 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* If there is no argument, print a new line.
If the second argument is -n, do not print a new line
Start procesing arguments from arg[2].
If there are more than one arguments, print them
Start processing arguments from arg[1]. */
void	ft_echo_option_n(char **arg, int *arg_index)
{
	if (!arg[1])
	{
		write(1, "\n", 1);
		*arg_index = -1;
	}
	else if (ft_strncmp(arg[1], "-n", ft_strlen(arg[0])) == 0)
		*arg_index = 2;
	else
		*arg_index = 1;
}

/* Loop through the arguments and check if curly braces
are found. If so, expand the argument. Else print the argument.
If there is more than one argument, print space and the arg.
Free memory and exit with status 0 */
void	ft_echo_as_forked(char **arg, t_ms *ms)
{
	int	arg_index;
	int	i;

	ft_echo_option_n(arg, &arg_index);
	if (arg_index != -1)
	{
		i = arg_index;
		while (arg[i])
		{
			if (arg[i][0] == '{' && arg[i][ft_strlen(arg[i]) - 1] == '}')
				ft_string_expansion(arg[i]);
			else
				write(1, arg[i], ft_strlen(arg[i]));
			if (arg[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (arg_index == 1)
		write(1, "\n", 1);
	free_and_exit(0, ms);
}

/* Loop through the arguments and check if curly braces
are found. If so, expand the argument. Else print the argument.
If there is more than one argument, print space and the arg. */
int	ft_echo_directly(char **arg)
{
	int	arg_index;
	int	i;

	ft_echo_option_n(arg, &arg_index);
	if (arg_index != -1)
	{
		i = arg_index;
		while (arg[i])
		{
			if (arg[i][0] == '{' && arg[i][ft_strlen(arg[i]) - 1] == '}')
				ft_string_expansion(arg[i]);
			else
				write(1, arg[i], ft_strlen(arg[i]));
			if (arg[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (arg_index == 1)
		write(1, "\n", 1);
	return (0);
}
