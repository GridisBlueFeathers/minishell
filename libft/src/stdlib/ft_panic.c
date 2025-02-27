/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_panic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:59:05 by svereten          #+#    #+#             */
/*   Updated: 2025/01/11 15:43:34 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/stdio.h"
#include "libft/stdlib.h"
#include <errno.h>

void	ft_panic(int status, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, STDERR_FILENO);
	else if (errno)
		perror(PANIC_MSG);
	ft_exit(status);
}
