/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:07:07 by svereten          #+#    #+#             */
/*   Updated: 2025/01/06 18:05:58 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static void	cmd_heredoc_handle(t_cmd *cmd, t_redir *redir)
{
	int		urandom_fd;
	int		i;
	int		c;
	char	*heredoc_line;

	(void)cmd;
	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd == -1)
		minishell_exit(1, NULL);
	redir->file_name = (char *)ft_calloc(22, sizeof(char));
	ft_strlcpy(redir->file_name, "/tmp/", 22);
	i = 0;
	while (i < 16)
	{
		// protect this read
		read(urandom_fd, &c, 1);
		c = c % 256;
		if (c == 47)
			continue ;
		redir->file_name[i + 5] = c;
		i++;
	}
	ft_close(urandom_fd);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
		minishell_exit(1, NULL);
	while (data(GET)->mode == IN_HEREDOC)
	{
		heredoc_line = readline(">");
		if (!heredoc_line)
			ft_putstr_fd("warning: heredoc delimited by EOF\n", STDERR_FILENO);
		if (!heredoc_line || !ft_strcmp(heredoc_line, redir->heredoc_delim))
			break ;
		write(redir->fd, heredoc_line, ft_strlen(heredoc_line));
		ft_free(STR, &heredoc_line);
	}
	ft_close(redir->fd);
	return ;
}

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
		cmd_heredoc_handle(cmd, cur);

		cur = cur->next;
	}
	return (1);
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
