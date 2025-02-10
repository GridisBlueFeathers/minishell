/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:27:54 by svereten          #+#    #+#             */
/*   Updated: 2025/02/10 15:47:02 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * "minishell: " strlen is 11
 * ": Is a directory\n" strlen is 17
 */
static char	*child_kill_directory(t_cmd *cmd)
{
	char	*msg;
	size_t	len;

	len = 11 + ft_strlen(cmd->bin) + 17;
	msg = (char *)ft_calloc(len + 1, sizeof(char));
	if (!msg)
		minishell_exit(1, NULL);
	ft_strlcat(msg, "minishell: ", len + 1);
	ft_strlcat(msg, cmd->name, len + 1);
	ft_strlcat(msg, ": Is a directory\n", len + 1);
	return (msg);
}

/**
 * "minishell: " strlen is 11
 * ": Permission denied\n" strlen is 20
 */
static char	*child_kill_permission(t_cmd *cmd)
{
	char	*msg;
	size_t	len;

	len = 11 + ft_strlen(cmd->bin) + 20;
	msg = (char *)ft_calloc(len + 1, sizeof(char));
	if (!msg)
		minishell_exit(1, NULL);
	ft_strlcat(msg, "minishell: ", len + 1);
	ft_strlcat(msg, cmd->name, len + 1);
	ft_strlcat(msg, ": Permission denied\n", len + 1);
	return (msg);
}

/**
 * "minishell: " strlen is 11
 * ": No such file or directory" strlen is 28
 *
 */
static char	*child_kill_file(t_cmd *cmd)
{
	char	*msg;
	size_t	len;

	len = 11 + ft_strlen(cmd->name) + 28;
	msg = (char *)ft_calloc(len + 1, sizeof(char));
	if (!msg)
		minishell_exit(1, NULL);
	ft_strlcat(msg, "minishell: ", len + 1);
	ft_strlcat(msg, cmd->name, len + 1);
	ft_strlcat(msg, ": No such file or directory\n", len + 1);
	return (msg);
}

/**
 * ": command not found\n" strlen is 20
 */
static char	*child_kill_command(t_cmd *cmd)
{
	char	*msg;
	size_t	len;

	len = ft_strlen(cmd->bin) + 20;
	msg = (char *)ft_calloc(len + 1, sizeof(char));
	if (!msg)
		minishell_exit(1, NULL);
	ft_strlcat(msg, cmd->name, len + 1);
	ft_strlcat(msg, ": command not found\n", len + 1);
	return (msg);
}

void	child_kill(t_cmd *cmd)
{
	int		code;
	char	*err_msg;

	if (is_directory(cmd->name))
	{
		err_msg = child_kill_directory(cmd);
		code = 126;
	}
	else if (access(cmd->bin, F_OK) == 0)
	{
		err_msg = child_kill_permission(cmd);
		code = 126;
	}
	else if (ft_strchr(cmd->name, '/'))
	{
		err_msg = child_kill_file(cmd);
		code = 127;
	}
	else
	{
		err_msg = child_kill_command(cmd);
		code = 127;
	}
	minishell_exit(code, err_msg);
}
