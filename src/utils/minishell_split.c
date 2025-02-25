/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:57:47 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:57:49 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ms_wordcount(char *str)
{
	size_t	i;
	size_t	words;

	i = 0;
	if (!str)
		return (0);
	words = 1;
	while (str[i])
	{
		if (str[i] == '|' && valid_operator(str, i, 0))
			words++;
		i++;
	}
	return (words);
}

static char	*ms_set_res(char *str, size_t last_loc, size_t loc)
{
	char	*res;

	if (!last_loc && !str[loc + 1])
		res = ft_substr(str, last_loc, loc + 1);
	else if (!last_loc)
		res = ft_substr(str, last_loc, loc);
	else if (!str[loc + 1])
		res = ft_substr(str, last_loc + 1, loc + 1);
	else
		res = ft_substr(str, last_loc + 1, loc - last_loc - 1);
	if (!res)
		minishell_exit(1, NULL);
	return (res);
}

char	**minishell_split(char *str)
{
	char	**res;
	size_t	i;
	size_t	y;
	size_t	last_loc;

	i = ms_wordcount(str);
	res = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!res)
		minishell_exit(1, NULL);
	i = 0;
	y = 0;
	last_loc = 0;
	while (str[i])
	{
		if ((str[i] == '|' && valid_operator(str, i, 0)) || !str[i + 1])
		{
			res[y] = ms_set_res(str, last_loc, i);
			last_loc = i;
			y++;
		}
		i++;
	}
	return (res);
}
