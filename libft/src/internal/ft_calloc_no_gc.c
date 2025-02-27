/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc_no_gc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:43:21 by svereten          #+#    #+#             */
/*   Updated: 2024/11/19 16:45:26 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"

void	*ft_calloc_no_gc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;
	size_t	res_size;

	res_size = nmemb * size;
	if (!nmemb || !size || res_size / size != nmemb)
		return (NULL);
	res = malloc(res_size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < res_size)
	{
		((char *)res)[i] = 0;
		i++;
	}
	return (res);
}
