/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:20:19 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 17:23:28 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"
#include "libft/strarr.h"
#include "libft/stdlib.h"

char	**ft_strarrdup(char **arr)
{
	char	**res;
	int		i;

	if (!arr)
		return (NULL);
	res = (char **)ft_calloc(ft_strarrlen(arr) + 1, sizeof(char *));
	if (!res)
		return (free(res), NULL);
	i = 0;
	while (arr[i])
	{
		res[i] = ft_strdup(arr[i]);
		if (!res[i])
			return (ft_free(STR_ARR, &res), NULL);
		i++;
	}
	return (res);
}
