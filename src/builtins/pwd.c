/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:14:10 by svereten          #+#    #+#             */
/*   Updated: 2025/02/17 16:36:14 by svereten         ###   ########.fr       */
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
