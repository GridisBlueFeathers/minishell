/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 10:44:08 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 17:15:24 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"

size_t	ft_strwcount(char const *str, char del)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	if (str[0] && str[0] != del)
		res++;
	while (str[i])
	{
		if (str[i] == del && str[i + 1] && str[i + 1] != del)
			res++;
		i++;
	}
	return (res);
}
