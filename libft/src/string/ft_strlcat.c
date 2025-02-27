/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:28:12 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 17:16:54 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	dst_len = 0;
	while (i < size && dst[i])
		i++;
	dst_len += i;
	while (i < size - 1 && src[i - dst_len])
	{
		dst[i] = src[i - dst_len];
		i++;
	}
	if (i < size)
		dst[i] = 0;
	return (dst_len + ft_strlen(src));
}
