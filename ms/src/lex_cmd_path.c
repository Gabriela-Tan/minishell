/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_cmd_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 10:37:19 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/03 11:18:05 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  Iterates through the list of commands and checks
what type of command each one is. If it is a builtin 
or an executable located at the specified path,
go forward (no action is needed). 
If not, find and construct the path */
void	ft_command_check(t_env *env)
{
	t_cmd	*current;

	current = env->cmd_head;
	while (current)
	{
		if (ft_check_builtin(current->cmd) == 1) ||
			if (access(cmd, X_OK) == 0)
		{
			current = current->next;
			continue;
		}
		else if (ft_isnopathx(current->cmd) == 1)
		{
			current->cmd = search_and_construct_path(current->cmd);
			current = current->next;
			continue;
		}
		else
			break;
	}
}

int ft_isnopathx(char *cmd)
{
	int i;
	char **paths;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strnstr(environ[i], "PATH", 4) != 0)
			break;
		i++;
	}
	if (environ[i] == NULL)
		return 0;
	paths = ft_split(environ[i] + 5, ':');
	int result = search_for_exec(paths, cmd);
	free_array(paths);
	return (result);
}

int search_for_exec(char **paths, char *cmd)
{
	int i;
	int path_length;
	int cmd_length;
	char *path;

	int i = 0;
	cmd_length = ft_strlen(cmd);
	while (paths[i] != NULL)
	{
		path_length = ft_strlen(paths[i]);
		path = malloc(path_length + cmd_length + 2);  // for '/' and '\0'
		if (path == NULL)
			return 0;
		ft_strlcpy(path, paths[i], path_length + 1);
		path[path_length] = '/';
		ft_strlcpy(path + path_length + 1, cmd, cmd_length + 1);
		if (access(path, X_OK) == 0)
		{
			free(path);
			return (1);
		}
		free(path);
		i++;
	}
	return (0);
}

char *search_and_construct_path(char **paths, char *cmd)
{
	int i;
	int cmd_length;
	char *new_cmd;

	i = 0;
	cmd_length = ft_strlen(cmd);
	new_cmd = NULL;
	while (paths[i] != NULL)
	{
		int path_length = ft_strlen(paths[i]);
		char *path = malloc(path_length + cmd_length + 2);  // for '/' and '\0'
		if (path == NULL)
			return NULL;
		ft_strlcpy(path, paths[i], path_length + 1);
		path[path_length] = '/';
		ft_strlcpy(path + path_length + 1, cmd, cmd_length + 1);
		if (access(path, X_OK) == 0)
		{
			new_cmd = path;
			break;
		}
		free(path);
		i++;
	}
	return new_cmd;
}

char *ft_return_path(char *cmd)
{
	int i;
	char **paths;
	char *new_cmd;

	i = 0;
	new_cmd = NULL;
	while (environ[i] != NULL)
	{
		if (ft_strnstr(environ[i], "PATH", 4) != 0)
			break;
		i++;
	}
	if (environ[i] == NULL)
		return NULL;
	paths = ft_split(environ[i] + 5, ':');
	new_cmd = search_and_construct_path(paths, cmd);
	free_array(paths);
	if (new_cmd != NULL)
		free(cmd);  // Free the old command as we are replacing it
	return new_cmd;
}