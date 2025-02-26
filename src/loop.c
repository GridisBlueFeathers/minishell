/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 15:00:00 by svereten         ###   ########.fr       */
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
	#if DEBUG
		dprintf(STDERR_FILENO, "lexer done\n");
	#endif
	parser();
	#if DEBUG
		dprintf(STDERR_FILENO, "parser done\n");
	#endif
	#if DEBUG
		debug_print();
	#endif
	executor();
	#if DEBUG
		dprintf(STDERR_FILENO, "executor done\n");
	#endif
}

void	loop(void)
{
	signal_init();
	while (1)
	{
		data(GET)->mode = IN_PROMPT;
		if (data(GET)->rl_prompt)
			ft_free(STR, &data(GET)->rl_prompt);
		if (data(GET)->exit_code)
			data(GET)->rl_prompt = readline(PREFIX_BAD);
		else
			data(GET)->rl_prompt = readline(PREFIX_GOOD);
		if (!data(GET)->rl_prompt)
		{
			ft_putstr_fd("exit\n", STDERR_FILENO);
			minishell_exit(data(GET)->exit_code, NULL);
		}
		data(GET)->line_num = 2;
		prompt_exec();
	}
}
