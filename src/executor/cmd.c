/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:07:07 by svereten          #+#    #+#             */
/*   Updated: 2025/01/14 17:13:38 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	cmd_heredoc_run(t_cmd *cmd)
{
	t_redir	*cur;

	dprintf(STDERR_FILENO, "Running heredocs for %s[%d]\n", cmd->name, cmd->index);
	cur = cmd->redir_head;
	while (cur)
	{
		if (cur->type != HEREDOC)
		{
			cur = cur->next;
			continue ;
		}
		dprintf(STDERR_FILENO, "Heredoc delim: %s\n", cur->heredoc_delim);
		heredoc_handle(cur);
		cur = cur->next;
	}
	return (data(GET)->mode);
}

int	cmd_execute(t_cmd *cmd)
{
	int		pipe_fd[2];

	dprintf(STDERR_FILENO, "Executing: %s[%d]\n", cmd->name, cmd->index);
	if (!cmd->redir_valid)
		return (0);
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
		child_execute(cmd, pipe_fd);
	if (cmd->index + 1 != data(GET)->cmd_amount)
	{
		ft_close(pipe_fd[WR]);
		redirect(pipe_fd[RD], STDIN_FILENO);
	}
	return (1);
}
