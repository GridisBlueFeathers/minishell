/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:18 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:07:57 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_exec(void)
{
	data(GET)->mode = IN_EXECUTION;
	if (!data(GET)->rl_prompt[0])
		return ;
	add_history(data(GET)->rl_prompt);
	if (!lexer())
		return ;
	parser();
	executor();
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
