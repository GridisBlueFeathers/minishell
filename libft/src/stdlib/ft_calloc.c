/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:56:08 by svereten          #+#    #+#             */
/*   Updated: 2025/01/11 17:18:02 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "internal.h"
#include "gc.h"
#include "libft/stdlib.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	t_data	data;

	data.ptr = ft_calloc_no_gc(nmemb, size);
	if (!data.ptr)
		return (NULL);
	if (!gc_data_add(PTR, data))
		return (free(data.ptr), NULL);
	return (data.ptr);
}
