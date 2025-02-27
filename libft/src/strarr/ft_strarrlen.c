/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:04:41 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 16:21:02 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/libft.h"

size_t	ft_strarrlen(char **arr)
{
	size_t	res;

	if (!arr)
		return (0);
	res = 0;
	while (arr[res])
	{
		res++;
	}
	return (res);
}
