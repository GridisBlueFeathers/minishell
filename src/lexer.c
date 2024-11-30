/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:26:48 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/30 14:41:25 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_quote_check(void)
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
		else if ((quote == '\'' && data(GET)->rl_prompt[i] == '\'')
			|| (quote == '"' && data(GET)->rl_prompt[i] == '"'))
			quote = 0;
		i++;
	}
	if (quote)
		return (0);
	return (1);
}

static int	lexer_pipe_check(void)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(data(GET)->rl_prompt, '|'))
		return (1);
	if (data(GET)->rl_prompt[i] == '|')
		return (0);
	while (ft_isspace(data(GET)->rl_prompt[i]))
		i++;
	if (data(GET)->rl_prompt[i] == '|')
		return (0);
	while (data(GET)->rl_prompt[i])
	{
		if (data(GET)->rl_prompt[i] == '|')
		{
			i++;
			while (ft_isspace(data(GET)->rl_prompt[i]))
				i++;
			if (!data(GET)->rl_prompt[i])
				return (0);
		}
		i++;
	}
	return (1);
}

int	lexer(void)
{
	if (!lexer_quote_check())
	{
		ft_putstr_fd("minishell: invalid use of quotation marks\n", 1);
		data(GET)->exit_code = 1;
		return (0);
	}
	if (!lexer_pipe_check())
	{
		ft_putstr_fd("minishell: syntax error near unexpected token '|'\n", 1);
		data(GET)->exit_code = 1;
		return (0);
	}
	return (1);
}
