/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:55:15 by svereten          #+#    #+#             */
/*   Updated: 2024/07/26 00:30:46 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	while (i < n && n)
	{
		if ((((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			|| !s1[i] || !s2[i])
		{
			res = ((unsigned char *)s1)[i] - ((unsigned char *)s2)[i];
			break ;
		}
		i++;
	}
	if (i > 0 && i == n)
		res = ((unsigned char *)s1)[i - 1] - ((unsigned char *)s2)[i - 1];
	return (res);
}
