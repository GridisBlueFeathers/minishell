/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:02:46 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 17:17:36 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"
#include "libft/stdlib.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	i;

	if (!s2)
		return (NULL);
	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	res = (char *)ft_calloc(s1_len + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (ft_free(STR, &s1), NULL);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[i - s1_len])
	{
		res[i] = s2[i - s1_len];
		i++;
	}
	return (ft_free(STR, &s1), res);
}
