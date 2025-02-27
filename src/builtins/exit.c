/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:53:04 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:09:09 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*numeric_arg_msg(t_cmd *cmd)
{
	char	*err_msg;
	size_t	len;

	len = 17 + ft_strlen(cmd->argv[1]) + 28;
	err_msg = (char *)ft_calloc(len + 1, sizeof(char));
	if (!err_msg)
		minishell_exit(1, NULL);
	ft_strlcat(err_msg, "minishell: exit: ", len + 1);
	ft_strlcat(err_msg, cmd->argv[1], len + 1);
	ft_strlcat(err_msg, ": numeric argument required\n", len + 1);
	return (err_msg);
}

/**
 * "minishell: exit: " strlen is 17
 * ": numeric argument required\n" strlen is 28
 */
int	builtin_exit(t_cmd *cmd)
{
	char	*err_msg;

	stdfd_close();
	if (cmd->pid)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (ft_strarrlen(cmd->argv) == 1)
		minishell_exit(data(GET)->exit_code, NULL);
	if (!ft_strlen(cmd->argv[1]) || !ft_isnumber(cmd->argv[1]))
	{
		err_msg = numeric_arg_msg(cmd);
		minishell_exit(2, err_msg);
	}
	if (ft_strarrlen(cmd->argv) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	minishell_exit(ft_atoi(cmd->argv[1]), NULL);
	return (0);
}
