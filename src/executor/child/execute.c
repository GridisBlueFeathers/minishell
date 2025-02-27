/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:54:19 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:07:15 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "command.h"
#include <errno.h>

static int	child_check_access(t_cmd *cmd, char *bin_path)
{
	if (!is_directory(bin_path) && access(bin_path, X_OK) == 0)
	{
		if (cmd->bin)
			ft_free(STR, &cmd->bin);
		cmd->bin = ft_strdup(bin_path);
		if (!cmd->bin)
			minishell_exit(1, NULL);
		ft_free(STR, &bin_path);
		cmd->from_path = 1;
		return (1);
	}
	if (!is_directory(bin_path) && access(bin_path, F_OK) == 0)
	{
		if (cmd->bin)
			ft_free(STR, &cmd->bin);
		cmd->bin = ft_strdup(bin_path);
		if (!cmd->bin)
			minishell_exit(1, NULL);
		cmd->from_path = 1;
	}
	return (0);
}

static void	child_get_path(t_cmd *cmd)
{
	char	*bin_path;
	int		i;
	size_t	len;

	i = 0;
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
	signal(SIGPIPE, signal_pipe);
	cmd_execute_single_builtin(cmd);
	minishell_exit(data(GET)->exit_code, NULL);
}

/**
 * "./" strlen is 2
 */
static void	child_handle_no_path(t_cmd *cmd)
{
	size_t	len;

	len = ft_strlen(cmd->name) + 2;
	cmd->bin = (char *)ft_calloc(len + 1, sizeof(char));
	if (!cmd->bin)
		minishell_exit(1, NULL);
	ft_strlcat(cmd->bin, "./", len + 1);
	ft_strlcat(cmd->bin, cmd->name, len + 1);
}

void	child_execute(t_cmd *cmd)
{
	if (cmd->type == BUILTIN)
		child_execute_builtin(cmd);
	if (ft_strchr(cmd->name, '/'))
	{
		cmd->bin = ft_strdup(cmd->name);
		if (!cmd->bin)
			minishell_exit(1, NULL);
	}
	else if (cmd->type == BIN && data(GET)->path && data(GET)->path[0])
		child_get_path(cmd);
	else if (cmd->type == BIN && (!data(GET)->path || !data(GET)->path[0]))
		child_handle_no_path(cmd);
	if (!cmd->bin)
	{
		cmd->bin = ft_strdup(cmd->name);
		if (!cmd->bin)
			minishell_exit(1, NULL);
	}
	execve(cmd->bin, cmd->argv, data(GET)->env_arr);
	if (errno == EACCES || errno == ENOENT)
		child_kill(cmd);
	minishell_exit(1, NULL);
}
