/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:54:24 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 16:14:17 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/stdio.h"
#include "libft/libft.h"
#include "internal.h"

static int	ft_format(va_list ap, int fd, char f)
{
	if (f == 'c')
		return (ft_putchar_fd(va_arg(ap, int), fd));
	if (f == 's')
		return (ft_putstr_fd(va_arg(ap, char *), fd));
	if (f == 'p')
		return (ft_putaddr_fd(va_arg(ap, void *), fd));
	if (f == 'd' || f == 'i')
		return (ft_putnbr_fd(va_arg(ap, int), fd));
	if (f == 'u')
		return (ft_putuint_fd(va_arg(ap, unsigned int), fd));
	if (f == 'x' || f == 'X')
		return (ft_putuhex_fd(va_arg(ap, unsigned int), fd, f));
	if (f == '%')
		return (ft_putchar_fd('%', fd));
	return (-1);
}

static int	ft_iterate_print(va_list ap, int fd, const char *fmt)
{
	size_t	len;
	size_t	i;
	int		bytes_written;

	i = 0;
	len = 0;
	while (fmt && fmt[i])
	{
		if (fmt[i + 1] && fmt[i] == '%')
		{
			bytes_written = ft_format(ap, fd, fmt[i + 1]);
			i++;
		}
		else
			bytes_written = ft_putchar_fd(fmt[i], fd);
		i++;
		if (bytes_written == -1)
			return (bytes_written);
		len += bytes_written;
	}
	return (len);
}

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list	ap;
	size_t	len;

	if (!fmt)
		return (-1);
	len = 0;
	va_start(ap, fmt);
	len = ft_iterate_print(ap, fd, fmt);
	va_end(ap);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	size_t	len;

	if (!fmt)
		return (-1);
	len = 0;
	va_start(ap, fmt);
	len = ft_iterate_print(ap, STDOUT_FILENO, fmt);
	va_end(ap);
	return (len);
}
