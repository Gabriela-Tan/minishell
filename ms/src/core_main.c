/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriela <gabriela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 08:20:57 by gabriela          #+#    #+#             */
/*   Updated: 2023/09/10 10:22:41 by gabriela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_ms	ms;
	char	*input;
	char	*prompt;

	ft_init(&ms);
//	signal(SIGINT, ft_sigint_handler);
//	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = ft_strjoin(getenv("USER"), " ^⨀ ᴥ ⨀ ^ ");
		input = readline(prompt);
		ft_handle_input(input, &ms, prompt);
		free(input);
	}
	return (0);
}
