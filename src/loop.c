/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/10 11:59:52 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_exec(void)
{
	if (data(GET)->rl_prompt[0] == '\n')
		return ;
	env_update();
	add_history(data(GET)->rl_prompt);
	if (!lexer())
		return ;
	printf("%s\n", data(GET)->rl_prompt);
	parser_init();
	debug_print();
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
			minishell_exit(0, NULL);
		prompt_exec();
		free(data(GET)->rl_prompt);
	}
}
