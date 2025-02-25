/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdfd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:28:06 by svereten          #+#    #+#             */
/*   Updated: 2025/02/25 15:39:10 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stdfd_copy(void)
{
	data(GET)->stdout_copy = dup(STDOUT_FILENO);
	if (data(GET)->stdout_copy < 0)
		minishell_exit(1, NULL);
	data(GET)->stdin_copy = dup(STDIN_FILENO);
	if (data(GET)->stdout_copy < 0)
		minishell_exit(1, NULL);
}

void	stdfd_restore(void)
{
	redirect(&data(GET)->stdout_copy, STDOUT_FILENO);
	redirect(&data(GET)->stdin_copy, STDIN_FILENO);
}

void	stdfd_close(void)
{
	if (data(GET)->stdout_copy >= 0 && close(data(GET)->stdout_copy) < 0)
		minishell_exit(1, NULL);
	if (data(GET)->stdin_copy >= 0 && close(data(GET)->stdin_copy) < 0)
		minishell_exit(1, NULL);
	data(GET)->stdout_copy = -1;
	data(GET)->stdin_copy = -1;
}
