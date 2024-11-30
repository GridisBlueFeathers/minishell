/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:26:48 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/30 13:11:18 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_quote_check(void)
{
	size_t	i;
	size_t	s_quote;
	size_t	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (data(GET)->rl_prompt[i])
	{
		if (!s_quote && !d_quote)
		{
			if (data(GET)->rl_prompt[i] == '"')
				d_quote = 1;
			else if (data(GET)->rl_prompt[i] == '\'')	
				s_quote = 1;
		}
		else if (s_quote && data(GET)->rl_prompt[i] == '\'')
			s_quote = 0;
		else if (d_quote && data(GET)->rl_prompt[i] == '"')
			d_quote = 0;
		i++;
	}
	if (s_quote || d_quote)
		printf("Invalid quotation, this will exit the program\n");
//		minishell_exit(1, "minishell: Invalid use of quotation marks");
}
