/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:58:09 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:58:14 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
