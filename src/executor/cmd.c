/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:07:07 by svereten          #+#    #+#             */
/*   Updated: 2025/01/31 13:29:23 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	cmd_execute_single_builtin(t_cmd *cmd)
{
	#if DEBUG
		dprintf(STDERR_FILENO, "Executing builtin\n");
	#endif
	if (ft_strncmp(cmd->name, "exit", ft_strlen("exit")) == 0)
		builtin_exit(cmd);
	if (ft_strncmp(cmd->name, "cd", ft_strlen("cd")) == 0)
		data(GET)->exit_code = builtin_cd(cmd);
	if (ft_strncmp(cmd->name, "env", ft_strlen("env")) == 0)
		data(GET)->exit_code = builtin_env(cmd);
}

int	cmd_heredoc_run(t_cmd *cmd)
{
	t_redir	*cur;

	#if DEBUG
	dprintf(STDERR_FILENO, "Running heredocs for %s[%d]\n", cmd->name, cmd->index);
	#endif
	cur = cmd->redir_head;
	while (cur)
	{
		if (cur->type != HEREDOC && cur->type != HRDC_EXPND)
		{
			cur = cur->next;
			continue ;
		}
		#if DEBUG
			dprintf(STDERR_FILENO, "Heredoc delim: %s\n", cur->heredoc_delim);
		#endif
		heredoc_handle(cur);
		cur = cur->next;
	}
	return (data(GET)->mode);
}

int	cmd_execute_single_bin(t_cmd *cmd)
{
	#if DEBUG
		dprintf(STDERR_FILENO, "Executing: %s[%d]\n", cmd->name, cmd->index);
	#endif
	cmd->pid = fork();
	if (cmd->pid < 0)
		minishell_exit(1, NULL);
	if (cmd->pid == 0)
		child_single(cmd);
	return (1);
}

int	cmd_execute(t_cmd *cmd)
{
	int		pipe_fd[2];

	#if DEBUG
		dprintf(STDERR_FILENO, "Executing: %s[%d]\n", cmd->name, cmd->index);
	#endif
	if (cmd->index + 1 != data(GET)->cmd_amount && pipe(pipe_fd) == -1)
		minishell_exit(1, NULL);
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		if (cmd->index + 1 != data(GET)->cmd_amount)
			pipe_close(pipe_fd);
		minishell_exit(1, NULL);
	}
	if (cmd->pid == 0)
		child(cmd, pipe_fd);
	if (cmd->index + 1 != data(GET)->cmd_amount)
	{
		ft_close(pipe_fd[WR]);
		redirect(&pipe_fd[RD], STDIN_FILENO);
	}
	return (1);
}
