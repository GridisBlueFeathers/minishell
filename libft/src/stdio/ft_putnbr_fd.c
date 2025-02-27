/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:17:58 by svereten          #+#    #+#             */
/*   Updated: 2024/11/22 17:43:46 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/stdio.h"

static int	ft_putnbr_fd_worker(int n, int mod, int fd)
{
	int	res;
	int	bytes_written;

	res = 0;
	if ((mod == -1 && n > -10) || (mod == 1 && n < 10))
		return (ft_putchar_fd((mod * n) + '0', fd));
	bytes_written = ft_putnbr_fd_worker(n / 10, mod, fd);
	if (bytes_written == -1)
		return (-1);
	res += bytes_written;
	bytes_written = ft_putnbr_fd_worker(n % 10, mod, fd);
	if (bytes_written == -1)
		return (-1);
	res += bytes_written;
	return (res);
}

int	ft_putnbr_fd(int n, int fd)
{
	int	res;
	int	bytes_written;
	int	mod;

	mod = 1;
	res = 0;
	if (n < 0)
	{
		bytes_written = ft_putchar_fd('-', fd);
		if (bytes_written == -1)
			return (-1);
		mod = -1;
		res++;
	}
	bytes_written = ft_putnbr_fd_worker(n, mod, fd);
	if (bytes_written == -1)
		return (-1);
	res += bytes_written;
	return (res);
}
