/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:59:41 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:59:43 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	wordcount(char *str)
{
	size_t	i;
	size_t	words;

	if (!str)
		return (0);
	i = 0;
	words = 0;
	while (str[i])
	{
		if (!isspace(str[i]))
		{
			i += wordlen(str + i);
			words++;
		}
		i++;
	}
	return (words);
}

size_t	wordlen(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (isredir(str[i]) && valid_operator(str, i, 0))
			break ;
		if (!quote && isquote(str[i]))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (isspace(str[i]) && !quote)
			break ;
		i++;
	}
	return (i);
}
