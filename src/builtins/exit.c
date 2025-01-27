/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 18:33:24 by svereten          #+#    #+#             */
/*   Updated: 2025/01/27 12:55:25 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/ctype.h"
#include "minishell.h"
#include <stdio.h>

/**
 * "minishell: exit: " strlen is 17
 * " numeric argument required\n" strlen is 27
 */
void	builtin_exit(char **args)
{
	char	*err_msg;
	size_t	len;

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (ft_strarrlen(args) == 1)
		minishell_exit(0, NULL);
	if (ft_isnumber(args[1]))
		minishell_exit(ft_atoi(args[1]), NULL);
	len = 17 + ft_strlen(args[1]) + 27;
	err_msg = (char *)ft_calloc(len + 1, sizeof(char));
	if (!err_msg)
		minishell_exit(1, NULL);
	ft_strlcat(err_msg, "minishell: exit:", len + 1);
	ft_strlcat(err_msg, args[1], len + 1);
	ft_strlcat(err_msg, " numeric argument required\n", len + 1);
	minishell_exit(2, err_msg);
}
