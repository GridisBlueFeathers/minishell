/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:09:47 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/11 15:09:53 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	valid_single_quote(char *str, size_t loc)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && i < loc)
	{
		if (str[i] == '\\' && str[i + 1] && isquote(str[i + 1]))
		{
			i += 2;
			continue ;
		}
		if (!quote && str[i] == '\'')
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

static char	valid_double_quote(char *str, size_t loc)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && i < loc)
	{
		if (str[i] == '\\' && str[i + 1] && isquote(str[i + 1]))
		{
			i += 2;
			continue ;
		}
		if (!quote && str[i] == '"')
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

static char	valid_quotes(char *str, size_t loc)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && i < loc)
	{
		if (str[i] == '\\' && str[i + 1] && isquote(str[i + 1]))
		{
			i += 2;
			continue ;
		}
		if (!quote && isquote(str[i]))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	return (quote);
}

int	valid_operator(char *str, size_t loc, char type)
{
	char	quote;

	quote = 0;
	if (type == '\'')
		quote = valid_single_quote(str, loc);
	else if (type == '"')
		quote = valid_double_quote(str, loc);
	else
		quote = valid_quotes(str, loc);
	if (quote)
		return (0);
	return (1);
}
