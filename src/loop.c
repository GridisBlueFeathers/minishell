/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/30 14:43:04 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_exec(void)
{
	if (data(GET)->rl_prompt[0] == '\n')
		return ;
	add_history(data(GET)->rl_prompt);
	if (!lexer())
		return ;
	printf("%s\n", data(GET)->rl_prompt);
	data(GET)->exit_code = 0;
}

void	loop(void)
{
	while (1)
	{
		if (data(GET)->exit_code)
			data(GET)->rl_prompt = readline("\uea76 minishell \uf061  ");
		else
			data(GET)->rl_prompt = readline("\ueab2 minishell \uf061  ");
		prompt_exec();
		free(data(GET)->rl_prompt);
	}
}
