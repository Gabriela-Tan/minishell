/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:36:40 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/22 12:36:08 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	command_counting(t_cmd *current)
{
	int		count;
	int		i;

	count = 1;
	i = 0;
	while (current->arg[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

void	ft_errorandexit(char *arg, t_ms *ms)
{
	printf("cd: %s: no such file or directory.\n", arg);
	fork_exit(1, ms);
}

void	ft_cd_fork(t_cmd *current, t_ms *ms)
{
	int		argument_count;
	char	old_pwd[1048];
	char	cwd[1048];

	argument_count = command_counting(current);
	if (argument_count > 2)
	{
		printf("cd: too many arguments\n");
		fork_exit(1, ms);
	}
	else
	{
		getcwd(old_pwd, 1048);
		if (argument_count == 1)
		{
			if (getenv("HOME"))
				chdir(getenv("HOME"));
			else
			{
				printf("cd: HOME not set\n");
				fork_exit(1, ms);
			}
		}
		else if (strcmp(current->arg[1], "-") == 0)
		{
			if (getenv("OLDPWD"))
				chdir(getenv("OLDPWD"));
			else 
			{
				printf("cd: OLDPWD not set\n");
				fork_exit(1, ms);
			}
		}
		else if (chdir(current->arg[1]) == -1)
			ft_errorandexit(current->arg[1], ms);
		getcwd(cwd, 1048);
		ft_rewrite(ft_checkforexisting("PWD"), join_env("PWD", cwd), ms);
		ft_rewrite(ft_checkforexisting("OLDPWD"), join_env("OLDPWD", old_pwd), ms);
		fork_exit(0, ms);
	}
}

int	ft_cd_nonfork(t_cmd *current, t_ms *ms)
{
	int	argument_count;
	char	old_pwd[1048];
	char	cwd[1048];

	argument_count = command_counting(current);
	if (argument_count > 2)
		return (printf("cd: too many arguments\n"), 256);
	else
	{
		if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		{
			perror("getcwd");
			return (256);
		}
		if (argument_count == 1) 
		{
			if (chdir(getenv("HOME")) == -1)
			{
				perror("chdir");
				return (256);
			}
		}
		else if (strcmp(current->arg[0], "-") == 0) 
		{
			if (chdir(getenv("OLDPWD")) == -1)
			{
				perror("chdir");
				return (256);
			}
		}
		else
		{
			if (chdir(current->arg[0]) == -1)
			{
				perror("chdir");
				return (256);
			}
		}
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
			return (256);
		}
		char *new_pwd = join_env("PWD", cwd);
		char *old_pwd_env = join_env("OLDPWD", old_pwd);
		ft_rewrite(ft_checkforexisting("PWD"), new_pwd, ms);
		ft_rewrite(ft_checkforexisting("OLDPWD"), old_pwd_env, ms);
		free(new_pwd); // Free allocated memory
		free(old_pwd_env); // Free allocated memory
	}
	return (0);
}

void	fork_exit(int status, t_ms *ms)
{
	free_cmd_list(ms->cmd_head);
	free_array(ms->env);
	exit(status);
}

char	*join_env(char *var, char *value)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = 0;
	j = 0;
	len = ft_strlen(var) + ft_strlen(value) + 1;
	result = (char *)malloc(len);
	if (result == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (var[i] != '\0')
	{
		result[i] = var[i];
		i++;
	}
	result[i++] = '=';
	while (value[j] != '\0')
		result[i++] = value[j++];
	result[i] = '\0';
	return (result);
}

void	ft_rewrite(int index, char *var, t_ms *ms)
{
	free(ms->env[index]);
	ms->env[index] = ft_strdup(var);
	environ[index] = ms->env[index];
}

int	ft_checkforexisting(char *var)
{
	int		i;
	char	**split;

	i = 0;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (ft_strncmp(split[0], var, ft_strlen(var)) == 0)
		{
			free_array(split);
			return (i);
		}
		else
			free_array(split);
		i++;
	}
	return (-1);
}