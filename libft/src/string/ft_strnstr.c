/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:26:05 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 17:17:03 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_len;
	char	*res;

	if (!big && !len)
		return (0);
	i = 0;
	res = 0;
	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *)big);
	while (big[i] && i < len - little_len + 1 && len >= little_len)
	{
		if (!ft_strncmp(&big[i], little, little_len))
		{
			res = &((char *)big)[i];
			break ;
		}
		i++;
	}
	return (res);
}
