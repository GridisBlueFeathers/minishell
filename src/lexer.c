/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:26:48 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/28 15:45:58 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_check(void)
{
	size_t	i;
	size_t	s_quote;
	size_t	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (data(GET)->rl_prompt[i])
	{
		if (data(GET)->rl_prompt[i] == '"')
			d_quote++;
		else if (data(GET)->rl_prompt[i] == '\'' && d_quote % 2)	
			s_quote++;
		i++;
	}
	if (s_quote % 2 || d_quote % 2)
		printf("Invalid quotation, this will exit the program\n");
//		minishell_exit(1, "minishell: Invalid use of quotation marks");
}
