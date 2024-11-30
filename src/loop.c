/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/30 16:36:09 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		add_history(data(GET)->rl_prompt);
		free(data(GET)->rl_prompt);
	}
}
