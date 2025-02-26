/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:59:30 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:59:32 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	valid_quote_type(char *str, size_t loc, char type)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && i < loc)
	{
		if (str[i] == '\\' && str[i + 1])
		{
			i += 2;
			continue ;
		}
		if (!quote && str[i] == type)
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
	if (type)
		quote = valid_quote_type(str, loc, type);
	else
		quote = valid_quotes(str, loc);
	if (quote)
		return (0);
	return (1);
}

static size_t	quote_type_valid(char *str, size_t loc, char type)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	if (!loc)
		return (1);
	while (str[i] && i < loc)
	{
		if (!quote && str[i] == type)
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		i++;
	}
	if (quote && str[loc] != quote)
		return (0);
	return (1);
}

int	quote_is_valid(char *str, size_t loc, char type)
{
	size_t	i;
	char	quote;

	if (type)
	{
		i = quote_type_valid(str, loc, type);
		if (i)
			return (1);
		return (0);
	}
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
