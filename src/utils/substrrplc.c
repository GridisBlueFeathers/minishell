/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substrrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:02:11 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 17:56:34 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	find_substr_loc(char *main, char *old)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (main[i])
	{
		if (!quote && isquote(main[i]))
			quote = main[i];
		else if (quote && main[i] == quote)
			quote = 0;
		if (!ft_strncmp(main + i, old, ft_strlen(old) - 1)
			&& quote != '\'')
			break ;
		i++;
	}
	return (i);
}

char	*substrrplc(char *main, char *old, char *new)
{
	size_t	i;
	char	*res;

	if (!old)
		return (main);
	res = NULL;
	i = find_substr_loc(main, old);
	if (i > 0)
	{
		res = ft_substr(main, 0, i);
		if (!res)
			minishell_exit(1, NULL);
	}
	if (new)
		res = ft_strjoin(res, new);
	res = ft_strjoin(res, (main + i + ft_strlen(old)));
	ft_free(STR, &main);
	return (res);
}
