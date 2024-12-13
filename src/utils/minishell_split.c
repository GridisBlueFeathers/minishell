/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 13:36:16 by jwolfram          #+#    #+#             */
/*   Updated: 2024/12/13 17:38:09 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_toggle_quotes(char *quote, char *str, int i)
{
	if (*quote && str[i] == '\\' && str[i + 1] && str[i + 1] == *quote)
		return (1);
	if (!*quote && (str[i] == '\'' || str[i] == '"'))
	{
		*quote = str[i];
		return (1);
	}
	else if (*quote && *quote == str[i])
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

static int	ms_strwcount(char *str)
{
	char	quote;
	size_t	i;
	size_t	words_num;

	i = 0;
	words_num = 1;
	quote = 0;
	while (str[i])
	{
		if (ms_toggle_quotes(&quote, str, i))
		{
			i++;
			if (quote && str[i] == quote && str[i - 1] == '\\')
				i++;
			continue ;
		}
		if (!quote && str[i] == '|')
			words_num++;
		i++;
	}
	return (words_num);
}

static int	ms_append_to_res(char **res, char *str)
{
	int		j;
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (ms_toggle_quotes(&quote, str, i))
		{
			i++;
			if (quote && str[i] == quote && str[i - 1] == '\\')
				i++;
			continue ;
		}
		if (!quote && str[i] == '|')
			break ;
		i++;
	}
	j = 0;
	while (res[j])
		j++;
	res[j] = ft_substr(str, 0, i);
	if (!res[j])
		return (0);
	return (1);
}

static int	ms_iterate_split(char *str, char **res)
{
	int		i;
	int		check;
	char	quote;

	i = 0;
	check = 1;
	quote = 0;
	while (str[i])
	{
		if (!i)
			check = ms_append_to_res(res, str + i);
		else if (!quote && str[i] == '|')
			check = ms_append_to_res(res, str + (i + 1));
		if (!check)
		{
			ft_free(STR_ARR, &res);
			return (0);
		}
		if (ms_toggle_quotes(&quote, str, i))
			i++;
		i++;
	}
	return (1);
}

char	**minishell_split(char *str)
{
	char	**res;
	int		words_num;

	if (!str)
		return (0);
	words_num = ms_strwcount(str);
	res = (char **)ft_calloc(words_num + 1, sizeof(char *));
	if (!res)
		return (0);
	if (!ms_iterate_split(str, res))
		return (0);
	return (res);
}
