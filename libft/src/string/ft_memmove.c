/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:11:51 by svereten          #+#    #+#             */
/*   Updated: 2024/07/26 00:26:54 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src && n)
		return (0);
	while (i < n)
	{
		if (dest < src)
			((char *)dest)[i] = ((char *)src)[i];
		else
			((char *)dest)[n - i - 1] = ((char *)src)[n - i - 1];
		i++;
	}
	return (dest);
}
