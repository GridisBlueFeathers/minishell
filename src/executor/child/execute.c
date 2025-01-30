/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:26:33 by svereten          #+#    #+#             */
/*   Updated: 2025/01/30 20:23:42 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "command.h"
#include <errno.h>
#include <stdio.h>

static int	child_check_access(t_cmd *cmd, char *bin_path)
{
	if (access(bin_path, X_OK) == 0)
	{
		if (cmd->bin)
			ft_free(STR, &cmd->bin);
		cmd->bin = ft_strdup(bin_path);
		if (!cmd->bin)
			minishell_exit(1, NULL);
		ft_free(STR, &bin_path);
		return (1);
	}
	if (access(bin_path, F_OK) == 0)
	{
		if (cmd->bin)
			ft_free(STR, &cmd->bin);
		cmd->bin = ft_strdup(bin_path);
		if (!cmd->bin)
			minishell_exit(1, NULL);
	}
	return (0);
}

static void	child_get_path(t_cmd *cmd)
{
	char	*bin_path;
	int		i;
	size_t	len;

	i = 0;
	#if DEBUG
		dprintf(STDERR_FILENO, "Getting path for the command\n");
	#endif
	while (data(GET)->path[i])
	{
		len = ft_strlen(data(GET)->path[i]) + ft_strlen(cmd->name) + 1;
		bin_path = (char *)ft_calloc(len + 1, sizeof(char));
		if (!bin_path)
			minishell_exit(1, NULL);
		ft_strlcat(bin_path, data(GET)->path[i], len + 1);
		ft_strlcat(bin_path, "/", len + 1);
		ft_strlcat(bin_path, cmd->name, len + 1);
		if (child_check_access(cmd, bin_path))
			break ;
		ft_free(STR, &bin_path);
		i++;
	}
}

static void	child_execute_builtin(t_cmd *cmd)
{
	cmd_execute_single_builtin(cmd);
	minishell_exit(data(GET)->exit_code, NULL);
}

void	child_execute(t_cmd *cmd)
{
	if (cmd->type == BUILTIN)
		child_execute_builtin(cmd);
	#if DEBUG
		dprintf(STDERR_FILENO, "Command name: %s\n", cmd->name);
		dprintf(STDERR_FILENO, "Command type: %d\n", cmd->type);
	#endif
	if (ft_strchr(cmd->name, '/'))
	{
		cmd->bin = ft_strdup(cmd->name);
		if (!cmd->bin)
			minishell_exit(1, NULL);
	}
	else if (cmd->type == BIN && data(GET)->path)
		child_get_path(cmd);
	if (!cmd->bin)
	{
		cmd->bin = ft_strdup(cmd->name);
		if (!cmd->bin)
			minishell_exit(1, NULL);
	}
	#if DEBUG
		dprintf(STDERR_FILENO, "Command bin: %s\n", cmd->bin);
	#endif
	execve(cmd->bin, cmd->argv, NULL);
	if (errno == EACCES || errno == ENOENT)
		child_kill(cmd);
	minishell_exit(1, NULL);
}
