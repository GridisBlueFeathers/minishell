/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:53:22 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:53:24 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		minishell_exit(1, NULL);
	if (ft_putendl_fd(cwd, STDOUT_FILENO) < 0)
	{
		ft_free(STR, &cwd);
		minishell_exit(1, NULL);
	}
	ft_free(STR, &cwd);
	return (0);
}
