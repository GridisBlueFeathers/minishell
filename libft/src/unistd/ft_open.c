/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:40:24 by svereten          #+#    #+#             */
/*   Updated: 2024/11/20 16:57:55 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "gc.h"
#include <fcntl.h>

int	ft_open(char *path, int oflag, int perm)
{
	int		res;
	t_data	data;

	res = open(path, oflag, perm);
	if (res < 0)
		return (res);
	data.fd = res;
	gc_data_add(FD, data);
	return (res);
}
