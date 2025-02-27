/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:54:10 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:07:00 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "minishell.h"
#include <fcntl.h>
#include <errno.h>

int	child_apply_redirs(t_cmd *cmd)
{
	t_redir	*cur;

	cur = cmd->redir_head;
	while (cur)
	{
		if (cur->type == INPUT
			|| cur->type == HEREDOC || cur->type == HRDC_EXPND)
			cur->fd = open(cur->file_name, O_RDONLY);
		if (cur->type == OUTPUT)
			cur->fd = open(cur->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cur->type == APPEND)
			cur->fd = open(cur->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cur->fd < 0)
			return (perror(cur->file_name), (errno = 0), 0);
		if (cur->type == INPUT
			|| cur->type == HEREDOC || cur->type == HRDC_EXPND)
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
	if (cmd->name)
		child_execute(cmd);
	minishell_exit(0, NULL);
}

void	child(t_cmd *cmd, int pipe_fd[2])
{
	stdfd_close();
	env_to_arr(cmd);
	if (cmd->idx + 1 != data(GET)->cmd_amount)
	{
		ft_close(pipe_fd[RD]);
		redirect(&pipe_fd[WR], STDOUT_FILENO);
	}
	if (!child_apply_redirs(cmd))
		minishell_exit(1, NULL);
	if (cmd->name)
		child_execute(cmd);
	minishell_exit(0, NULL);
}
