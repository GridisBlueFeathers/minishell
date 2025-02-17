/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_rm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 15:07:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/13 15:57:11 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	quotes_esc(char *str, char *res, size_t *i, size_t *j)
{
	int	idx;

	idx = *i;
	if (str[idx] == '"')
	{
		res[0] = '"';
		return (1);
	}
	else if (str[idx] == '\'' && valid_operator(str, idx, 0))
	{
		res[0] = '\'';
		return (1);
	}
	res[0] = '\\';
	res[1] = '\'';
	*i += 1;
	*j += 1;
	return (0);
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
		else if (isquote(str[i]) && quote_is_valid(str, i, 0))
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
		else if (isquote(str[i]) && quote_is_valid(str, i, 0))
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
		if (token->tok_type == HEREDOC && !str_has_quotes(token->next->tok_str))
			token->tok_type = HRDC_EXPND;
		if (ft_strchr(token->tok_str, '"') || ft_strchr(token->tok_str, '\''))
		{
			quote_amount = quote_amount_get(token->tok_str);
			token->tok_str = quotes_rm(token->tok_str, quote_amount);
		}
		token = token->next;
	}
}
