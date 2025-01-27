/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/27 15:04:49 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_exec(void)
{
	if (!data(GET)->rl_prompt[0])
		return ;
	add_history(data(GET)->rl_prompt);
	printf("Prompt: %s\n", data(GET)->rl_prompt);
	if (!lexer())
		return ;
	parser();
	debug_print();
	executor();
	data(GET)->exit_code = 0;
}

void	loop(void)
{
	signal_init();
	while (1)
	{
		if (data(GET)->exit_code)
			data(GET)->rl_prompt = readline(PREFIX_BAD);
		else
			data(GET)->rl_prompt = readline(PREFIX_GOOD);
		if (!data(GET)->rl_prompt)
		{
			printf("exit\n");
			minishell_exit(0, NULL);
		}
		prompt_exec();
		free(data(GET)->rl_prompt);
	}
}
