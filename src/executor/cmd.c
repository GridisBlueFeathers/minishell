/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:54:35 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:07:35 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_execute_multiple_builtin(t_cmd *cmd)
{
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

void	cmd_execute_single_builtin(t_cmd *cmd)
{
	if (data(GET)->cmd_amount == 1)
	{
		stdfd_copy();
		if (!child_apply_redirs(cmd))
		{
			data(GET)->exit_code = 1;
			stdfd_restore();
			return ;
		}
	}
	cmd_execute_multiple_builtin(cmd);
}

int	cmd_heredoc_run(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redir_head;
	while (cur)
	{
		if (cur->type != HEREDOC && cur->type != HRDC_EXPND)
		{
			cur = cur->next;
			continue ;
		}
		data(GET)->mode = IN_HEREDOC;
		heredoc_handle(cur);
		cur = cur->next;
	}
	return (data(GET)->mode);
}

int	cmd_execute_single_bin(t_cmd *cmd)
{
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
