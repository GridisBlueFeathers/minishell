/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/20 14:35:20 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

static void	prompt_exec(void)
{
	data(GET)->mode = IN_EXECUTION;
	if (!data(GET)->rl_prompt[0])
		return ;
	add_history(data(GET)->rl_prompt);
	#if DEBUG
		printf("Prompt: %s\n", data(GET)->rl_prompt);
	#endif
	if (!lexer())
		return ;
	parser();
	#if DEBUG
		debug_print();
	#endif
	executor();
}

void	loop(void)
{
	signal_init();
	while (1)
	{
		data(GET)->mode = IN_PROMPT;
		if (data(GET)->exit_code)
			data(GET)->rl_prompt = readline(PREFIX_BAD);
		else
			data(GET)->rl_prompt = readline(PREFIX_GOOD);
		if (!data(GET)->rl_prompt)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			minishell_exit(data(GET)->exit_code, NULL);
		}
		prompt_exec();
		free(data(GET)->rl_prompt);
	}
}
