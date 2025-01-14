/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substrrplc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:02:11 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/11 15:05:01 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substrrplc(char *main, char *old, char *new)
{
	size_t	i;
	char	*res;

	if (!old)
		return (main);
	i = 0;
	res = NULL;
	while (main[i])
	{
		if (!ft_strncmp(main + i, old, ft_strlen(old) - 1)
			&& valid_operator(main, i, '\''))
			break ;
		i++;
	}
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
