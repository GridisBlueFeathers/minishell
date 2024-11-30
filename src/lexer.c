/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:26:48 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/30 13:28:42 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_quote_check(void)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (data(GET)->rl_prompt[i])
	{
		if (!quote)
		{
			if (data(GET)->rl_prompt[i] == '"'
				|| data(GET)->rl_prompt[i] == '\'')
				quote = data(GET)->rl_prompt[i];
		}
		else if (quote == '\'' && data(GET)->rl_prompt[i] == '\'')
			quote = 0;
		else if (quote == '"' && data(GET)->rl_prompt[i] == '"')
			quote = 0;
		i++;
	}
	if (quote)
		printf("Invalid quotation, this will exit the program\n");
//		minishell_exit(1, "minishell: Invalid use of quotation marks");
}

void	lexer(void)
{
	lexer_quote_check();
}
