/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:36:16 by jwolfram          #+#    #+#             */
/*   Updated: 2024/12/19 16:17:10 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	ms_valid_pipe(char *str, size_t loc)
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
		if (str[i] == '|' && ms_valid_pipe(str, i))
			words++;
		i++;
	}
	return (words);
}

static char 	*ms_set_res(char *str, size_t last_loc, size_t loc)
{
	char	*res;
	
	if (!last_loc && !str[loc + 1])
		res = ft_substr(str, last_loc, loc + 1);
	else if (!last_loc)
		res = ft_substr(str, last_loc, loc);
	else if (!str[loc + 1])
		res = ft_substr(str, last_loc + 1, loc + 1);
	else
		res = ft_substr(str, last_loc + 1, ft_strlen(str) - loc);
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
	printf("we have %zu words\n", i);
	res = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!res)
		minishell_exit(1, NULL);
	i = 0;
	y = 0;
	last_loc = 0;
	while (str[i])
	{
		if ((str[i] == '|' && ms_valid_pipe(str, i)) || !str[i + 1])
		{
			printf("%zu\n", i);
			res[y] = ms_set_res(str, last_loc, i);
			last_loc = i;
			y++;
		}
		i++;
	}
	return (res);
}
