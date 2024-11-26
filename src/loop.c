/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/26 18:38:24 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	loop(void)
{
	while (1)
	{
		if (data(GET)->exit_code)
			data(GET)->rl_prompt = readline("\uea76 minishell \uf061  ");
		else
			data(GET)->rl_prompt = readline("\ueab2 minishell \uf061  ");
		printf("%s\n", data(GET)->rl_prompt);
		add_history(data(GET)->rl_prompt);
		free(data(GET)->rl_prompt);
	}
}
