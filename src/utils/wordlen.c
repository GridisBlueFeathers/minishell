/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:58:12 by jwolfram          #+#    #+#             */
/*   Updated: 2024/12/13 17:00:43 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	wordlen(char *str)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	if (!str)
		return (0);
	while (str[i] && !isredir(str[i]))
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (isspace(str[i]) && !quote)
			break ;
		i++;
	}
	return (i);
}
