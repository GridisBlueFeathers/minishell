/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 12:09:47 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/06 12:35:24 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_operator(char *str, size_t loc)
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
	if (quote)
		return (0);
	return (1);
}
