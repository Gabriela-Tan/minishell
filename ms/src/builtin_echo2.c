/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:34:48 by gabriela          #+#    #+#             */
/*   Updated: 2023/10/15 09:13:34 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Trim the curly braces from the string to be expanded.
Split the trimmed string into two substrings delimited by a dot.
If the substrings are numbers, expand them as numbers. 
If the substrings are characters, expand them as characters.
Otherwise, print the original string. Free memory. */
void	ft_string_expansion(char *word)
{
	char	**split;
	char	*trimmed;

	trimmed = ft_strtrim(word, "{}");
	split = ft_split(trimmed, '.');

	if ((ft_strlen(split[0]) > 1) || ft_strlen(split[1]) > 1)
	{
		if (ft_num_string(split, 0, 0) == 0)
			ft_expand_num_str(ft_atoi(split[0]), ft_atoi(split[1]));
		else
			write(1, word, ft_strlen(word));
	}
	else if ((split[0][0] < '1' || split[0][0] > '9')
		&& (split[1][0] < '1' || split[1][0] > '9'))
		ft_expand_char_str(split[0][0], split[1][0]);
	else
		write(1, word, ft_strlen(word));
	free(trimmed);
	free_array(split);
}

/* Flag is used to determine if the expansion should 
be done in ascending or descending order. Run a loop
until the first character matches the last character,
either decrementing or incrementing the character. */
void	ft_expand_char_str(char first, char last)
{
	int	flag;

	if (first <= last)
		flag = 1;
	else
		flag = -1;
	while (first != last)
	{
		write(1, &first, 1);
		write(1, " ", 1);
		first += flag;
	}
	write(1, &last, 1);
}

/* Flag is used to determine if the expansion should 
be done in ascending or descending order. Run a loop
until the first number matches the last number,
either decrementing or incrementing the number. */
void	ft_expand_num_str(int first, int last)
{
	int	flag;

	if (first <= last)
		flag = 1;
	else
		flag = -1;
	while (first != last)
	{
		ft_putnbr_fd(first, 1);
		write(1, " ", 1);
		first += flag;
	}
	ft_putnbr_fd(last, 1);
}

/* return 1 if there is a character in the string
which is not a number */
int	ft_num_string(char **arg, int i, int j)
{
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (!ft_isdigit(arg[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
