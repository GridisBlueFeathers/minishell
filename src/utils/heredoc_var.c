/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:16:28 by svereten          #+#    #+#             */
/*   Updated: 2025/02/21 13:47:51 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

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
