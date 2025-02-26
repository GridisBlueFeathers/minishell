/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdfd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:58:28 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 17:04:17 by svereten         ###   ########.fr       */
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
	if (data(GET)->stdout_copy >= 0)
		redirect(&data(GET)->stdout_copy, STDOUT_FILENO);
	if (data(GET)->stdin_copy >= 0)
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
