/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:58 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:55:59 by jwolfram         ###   ########.fr       */
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
		expander_init(data(GET)->prompt[i]);
		token_init(data(GET)->prompt[i]);
		quotes_rm_init(data(GET)->prompt[i]->first);
		i++;
	}
	command_table_init();
}
