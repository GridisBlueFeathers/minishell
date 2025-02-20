/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:07:07 by svereten          #+#    #+#             */
/*   Updated: 2025/02/20 15:22:21 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>

void	cmd_execute_single_builtin(t_cmd *cmd)
{
	#if DEBUG
		dprintf(STDERR_FILENO, "Executing builtin\n");
	#endif
	if (data(GET)->cmd_amount == 1)
	{
		stdfd_copy();
		if (!child_apply_redirs(cmd))
		{
			(data(GET)->exit_code = 1, stdfd_restore());
			return ;
		}
	}
	if (ft_strcmp(cmd->name, "exit") == 0)
		data(GET)->exit_code = builtin_exit(cmd);
	if (ft_strcmp(cmd->name, "cd") == 0)
		data(GET)->exit_code = builtin_cd(cmd);
	if (ft_strcmp(cmd->name, "env") == 0)
		data(GET)->exit_code = builtin_env(cmd);
	if (ft_strcmp(cmd->name, "export") == 0)
		data(GET)->exit_code = builtin_export(cmd);
	if (ft_strcmp(cmd->name, "unset") == 0)
		data(GET)->exit_code = builtin_unset(cmd);
	if (ft_strcmp(cmd->name, "pwd") == 0)
		data(GET)->exit_code = builtin_pwd();
	if (ft_strcmp(cmd->name, "echo") == 0)
		data(GET)->exit_code = builtin_echo(cmd);
	if (data(GET)->cmd_amount == 1)
		stdfd_restore();
}

int	cmd_heredoc_run(t_cmd *cmd)
{
	t_redir	*cur;

	#if DEBUG
	dprintf(STDERR_FILENO, "Running heredocs for %s[%d]\n", cmd->name, cmd->idx);
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
		data(GET)->mode = IN_HEREDOC;
		heredoc_handle(cur);
		cur = cur->next;
	}
	return (data(GET)->mode);
}

int	cmd_execute_single_bin(t_cmd *cmd)
{
	#if DEBUG
		dprintf(STDERR_FILENO, "Executing: %s[%d]\n", cmd->name, cmd->idx);
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
		dprintf(STDERR_FILENO, "Executing: %s[%d]\n", cmd->name, cmd->idx);
	#endif
	if (cmd->idx + 1 != data(GET)->cmd_amount && pipe(pipe_fd) == -1)
		minishell_exit(1, NULL);
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		if (cmd->idx + 1 != data(GET)->cmd_amount)
			pipe_close(pipe_fd);
		minishell_exit(1, NULL);
	}
	if (cmd->pid == 0)
		child(cmd, pipe_fd);
	if (cmd->idx + 1 != data(GET)->cmd_amount)
	{
		ft_close(pipe_fd[WR]);
		redirect(&pipe_fd[RD], STDIN_FILENO);
	}
	return (1);
}
