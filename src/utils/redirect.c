/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 11:56:50 by svereten          #+#    #+#             */
/*   Updated: 2025/01/23 17:57:34 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>

void	redirect(int *old_fd, int new_fd)
{
	if (!old_fd)
		return ;
	if (dup2(*old_fd, new_fd) == -1)
		minishell_exit(1, NULL);
	if (*old_fd >= 0 && close(*old_fd) == -1)
		minishell_exit(1, NULL);
	*old_fd = -1;
}
