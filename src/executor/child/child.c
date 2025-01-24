/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:18:07 by svereten          #+#    #+#             */
/*   Updated: 2025/01/24 17:26:10 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "command.h"
#include "minishell.h"
#include <fcntl.h>

static int	child_apply_redirs(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redir_head;
	while (cur)
	{
		if (cur->type == INPUT || cur->type == HEREDOC)
			cur->fd = open(cur->file_name, O_RDONLY);
		if (cur->type == OUTPUT)
			cur->fd = open(cur->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cur->type == APPEND)
			cur->fd = open(cur->file_name, O_WRONLY | O_CREAT, 0644);
		if (cur->fd < 0)
			return (0);
		if (cur->type == INPUT || cur->type == HEREDOC)
			redirect(&cur->fd, STDIN_FILENO);
		if (cur->type == OUTPUT || cur->type == APPEND)
			redirect(&cur->fd, STDOUT_FILENO);
		cur = cur->next;
	}
	return (1);
}

void	child_single(t_cmd *cmd)
{
	if (!child_apply_redirs(cmd))
		minishell_exit(1, NULL);
	child_execute(cmd);
}

void	child(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->index + 1 != data(GET)->cmd_amount)
	{
		ft_close(pipe_fd[RD]);
		redirect(&pipe_fd[WR], STDOUT_FILENO);
	}
	else
		redirect(&data(GET)->stdout_copy, STDOUT_FILENO);
	stdfd_close();
	if (!child_apply_redirs(cmd))
		minishell_exit(1, NULL);
	child_execute(cmd);
}
