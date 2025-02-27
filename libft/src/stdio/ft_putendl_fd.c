/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:15:16 by svereten          #+#    #+#             */
/*   Updated: 2024/11/22 17:43:24 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/stdio.h" 

int	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return (write(fd, "(null)\n", 7));
	return (ft_putstr_fd(s, fd) + ft_putchar_fd('\n', fd));
}
