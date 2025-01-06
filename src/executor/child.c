/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:05:03 by svereten          #+#    #+#             */
/*   Updated: 2025/01/06 16:05:25 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	child_apply_redirs(t_cmd *cmd)
{
	(void)cmd;
	return (1);
}

void	child_execute(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->index + 1 != data(GET)->cmd_amount)
	{
		ft_close(pipe_fd[RD]);
		redirect(pipe_fd[WR], STDOUT_FILENO);
	}
	else
		redirect(data(GET)->stdout_copy, STDOUT_FILENO);
	if (!child_apply_redirs(cmd))
		minishell_exit(1, NULL);
	if (execve(cmd->bin, cmd->argv, NULL))
		minishell_exit(0, NULL);
}
