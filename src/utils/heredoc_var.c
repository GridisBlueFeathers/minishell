/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:57:00 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:57:02 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_var(char *str, size_t loc)
{
	size_t	i;
	int		heredoc;

	i = 0;
	heredoc = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			while (isspace(str[i]) || isquote(str[i]))
				i++;
			if (str[i] == '$' && i == loc)
				return (1);
		}
		i++;
	}
	return (0);
}
