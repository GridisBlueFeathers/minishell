/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 19:50:29 by svereten          #+#    #+#             */
/*   Updated: 2024/11/22 17:21:58 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/stdlib.h"

static int	ft_intlen(int n)
{
	int	res;

	res = 1;
	if (n < 0)
		res++;
	while (n / 10)
	{
		res++;
		n /= 10;
	}
	return (res);
}

static void	ft_append_char(char *res, char c)
{
	int	i;

	i = 0;
	while (res[i])
		i++;
	res[i] = c;
}

static void	ft_itoa_worker(char *res, int n, int mod)
{
	if ((mod == -1 && n > -10) || (mod == 1 && n < 10))
	{
		ft_append_char(res, (n * mod) + '0');
		return ;
	}
	ft_itoa_worker(res, n / 10, mod);
	ft_itoa_worker(res, n % 10, mod);
}

char	*ft_itoa(int n)
{
	int		mod;
	char	*res;

	res = (char *)ft_calloc(ft_intlen(n) + 1, sizeof(char));
	if (!res)
		return (NULL);
	mod = 1;
	if (n < 0)
	{
		ft_append_char(res, '-');
		mod = -1;
	}
	ft_itoa_worker(res, n, mod);
	return (res);
}
