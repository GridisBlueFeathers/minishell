/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:37:45 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 17:20:25 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"
#include "libft/stdlib.h"

static int	ft_append_to_res(char **res, char const *s, char c, int start)
{
	int		j;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i + start] != c && s[i + start])
	{
		i++;
		len++;
	}
	j = 0;
	while (res[j])
		j++;
	res[j] = ft_substr(s, start, len);
	if (!res[j])
		return (0);
	return (1);
}

static int	ft_iterate_split(char const *s, char c, char **res)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	while (s[i])
	{
		if (!i && s[i] != c)
			check = ft_append_to_res(res, s, c, i);
		else if (s[i] == c && s[i + 1] != c && s[i + 1])
			check = ft_append_to_res(res, s, c, i + 1);
		if (!check)
		{
			ft_free(STR_ARR, &res);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		words_num;

	if (!s)
		return (0);
	words_num = ft_strwcount(s, c);
	res = (char **)ft_calloc(words_num + 1, sizeof(char *));
	if (!res)
		return (0);
	if (!ft_iterate_split(s, c, res))
		return (0);
	return (res);
}
