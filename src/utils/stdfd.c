/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdfd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:28:06 by svereten          #+#    #+#             */
/*   Updated: 2025/01/06 15:34:51 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	stdfd_copy(void)
{
	data(GET)->stdin_copy = dup(STDIN_FILENO);
	if (data(GET)->stdin_copy < 0)
		minishell_exit(1, NULL);
	data(GET)->stdout_copy = dup(STDOUT_FILENO);
	if (data(GET)->stdout_copy < 0)
		minishell_exit(1, NULL);
}

void	stdfd_reset(void)
{
	if (dup2(data(GET)->stdin_copy, STDIN_FILENO) < 0)
		minishell_exit(1, NULL);
	if (dup2(data(GET)->stdout_copy, STDOUT_FILENO) < 0)
		minishell_exit(1, NULL);
}

void	stdfd_close(void)
{
	if (close(data(GET)->stdin_copy) < 0)
		minishell_exit(1, NULL);
	if (close(data(GET)->stdout_copy) < 0)
		minishell_exit(1, NULL);
}
