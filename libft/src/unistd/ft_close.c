/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:58:40 by svereten          #+#    #+#             */
/*   Updated: 2025/01/11 17:20:13 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "gc.h"
#include <unistd.h>

int	ft_close(int fd)
{
	t_data	data;

	if (fd < 0)
		return (0);
	if (close(fd) == -1)
		return (-1);
	data.fd = fd;
	gc_data_remove(FD, data);
	return (0);
}
