/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 15:06:35 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/03 11:08:17 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init(t_env *env)
{
	env->cmd_head = NULL;
	env->i_cmd = -1;
	env->delim = NULL;
	env->in_fd = -1;
	env->out_fd = -1;
	env->saved_stdin = -1;
	env->saved_stdout = -1;
}
