/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:07:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/11 12:33:54 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	quote_is_valid(char *str, size_t loc)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	if (!loc)
		return (1);
	while (str[i] && i < loc)
	{
		if (!quote && isquote(str[i]))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	if (quote && str[loc] != quote)
		return (0);
	return (1);
}

static void	quotes_iterate(char *str, char *res)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && isquote(str[i + 1]))
		{
			i++;
			if (!quotes_esc(str, res + j, &i, &j))
				continue ;
		}
		else if (isquote(str[i]) && quote_is_valid(str, i))
		{
			i++;
			continue ;
		}
		else
			res[j] = str[i];
		i++;
		j++;
	}
}

static char	*quotes_rm(char *str, size_t quote_amount)
{
	char	*res;

	res = (char *)ft_calloc((ft_strlen(str) - quote_amount + 1), sizeof(char));
	if (!res)
		minishell_exit(1, NULL);
	quotes_iterate(str, res);
	return (res);
}

static size_t	quote_amount_get(char *str)
{
	size_t	i;
	size_t	amount;

	i = 0;
	amount = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] == '"')
			i++;
		else if (isquote(str[i]) && quote_is_valid(str, i))
			amount++;
		i++;
	}
	return (amount);
}

void	quotes_rm_init(t_token	*token)
{
	size_t	quote_amount;

	quote_amount = 0;
	while (token)
	{
		if (token->tok_type == HEREDOC && !isquote(token->next->tok_str[0]))
			token->tok_type = HRDC_EXPND;
		if (ft_strchr(token->tok_str, '"') || ft_strchr(token->tok_str, '\''))
		{
			quote_amount = quote_amount_get(token->tok_str);
			token->tok_str = quotes_rm(token->tok_str, quote_amount);
		}
		token = token->next;
	}
}
