/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:51:25 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/27 14:47:28 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(void)
{
	size_t		i;

	i = 0;
	prompt_init();
	while (data(GET)->prompt[i])
	{
		data(GET)->prompt[i]->idx = i;
		token_init(data(GET)->prompt[i]);
		expander_init(data(GET)->prompt[i]->first);
		quotes_rm_init(data(GET)->prompt[i]->first);
		i++;
	}
	command_table_init();
}
