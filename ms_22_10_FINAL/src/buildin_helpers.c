/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvocasko <mvocasko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 02:38:37 by mvocasko          #+#    #+#             */
/*   Updated: 2023/10/21 23:52:14 by mvocasko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//custom strcmp

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

//function that helps determine the length of array of strings
//by counting the number of non-NULL elements in the array

size_t	ft_array_len(char **array)
{
	size_t	len;

	len = 0;
	while (array[len] != NULL)
		len++;
	return (len);
}
//custom strcpy

char	*ft_strcpy(char *dest, const char *src)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (*s)
	{
		*d = *s;
		d++;
		s++;
	}
	*d = '\0';
	return (dest);
}

//custom strcat

char	*ft_strcat(char *dest, const char *src)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (*d)
		d++;
	while (*s)
	{
		*d = *s;
		d++;
		s++;
	}
	*d = '\0';
	return (dest);
}

//my own realloc

void	ft_realloc(char ***ptr, size_t new_size)
{
	size_t		i;
	char		**new_ptr;

	new_ptr = (char **)malloc(new_size * sizeof(char *));
	if (new_ptr == NULL)
	{
		perror("Failed to reallocate memory.");
		exit(1);
	}
	if (*ptr != NULL)
	{
		i = 0;
		while ((*ptr)[i] != NULL)
		{
			new_ptr[i] = (*ptr)[i];
			i++;
		}
		free(*ptr);
	}
	*ptr = new_ptr;
}
