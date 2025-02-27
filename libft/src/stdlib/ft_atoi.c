/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 19:22:54 by svereten          #+#    #+#             */
/*   Updated: 2024/11/22 15:49:03 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/ctype.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	mod;
	int	res;

	i = 0;
	mod = 1;
	res = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			mod = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		res = res * 10 + mod * (nptr[i] - '0');
		i++;
	}
	return (res);
}
