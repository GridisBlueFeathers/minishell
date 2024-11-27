/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/27 17:14:25 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(void)
{
	while (1)
	{
		signal(SIGINT, signal_int);
		if (data(GET)->exit_code)
			data(GET)->rl_prompt = readline(PREFIX_BAD);
		else
			data(GET)->rl_prompt = readline(PREFIX_GOOD);
		if (!data(GET)->rl_prompt)
			minishell_exit(0, NULL);
		if (!ft_strcmp(data(GET)->rl_prompt, "yo wtf"))
			data(GET)->exit_code = 1;
		else
			data(GET)->exit_code = 0;
		printf("%s\n", data(GET)->rl_prompt);
		printf("%d\n", data(GET)->rl_prompt[0]);
		add_history(data(GET)->rl_prompt);
		free(data(GET)->rl_prompt);
	}
}
