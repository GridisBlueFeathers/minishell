/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:08:58 by svereten          #+#    #+#             */
/*   Updated: 2025/01/06 14:58:50 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>





/*static int	cmd_execute_on_pipe(t_cmd *cmd)
{
	(void)cmd;
	return (1);
}*/


/*static int	cmd_execute_single(t_cmd *cmd)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		minishell_exit(1, NULL);
	if (cmd->pid == 0)
		cmd_execute_child(cmd, NULL);

	return (1);
}*/


static void	cmd_free(t_cmd *cmd)
{
	t_redir	*cur;
	t_redir	*tmp;

	ft_free(STR, &cmd->bin);
	ft_free(STR, &cmd->name);
	ft_free(STR_ARR, &cmd->argv);
	cur = cmd->redir_head;
	while (cur)
	{
		tmp = cur->next;
		if (cur->type == HEREDOC)
			unlink(cur->file_name);
		ft_free(STR, &cur->file_name);
		ft_close(cur->fd);
		cur = tmp;
	}
	ft_free(STRUCT, &cmd);
	return ;
}

static void	commands_reset(void)
{
	int	i;

	i = 0;
	while (data(GET)->commands[i])
	{
		cmd_free(data(GET)->commands[i]);
		i++;
	}
	ft_free(STRUCT, &data(GET)->commands);
	data(GET)->cmd_amount = 0;
}

static void	cmd_heredoc_run(t_cmd *cmd)
{
	t_redir	*cur;

	dprintf(STDERR_FILENO, "Running heredocs\n");
	return ;
	cur = cmd->redir_head;
	while (cur) 
	{
		if (cur->type != HEREDOC)
		{
			cur = cur->next;
			continue ;
		}
	}
}

static int	cmd_apply_redirs(t_cmd *cmd)
{
	(void)cmd;
	return (1);
}

static void	cmd_execute_child(t_cmd *cmd, int pipe_fd[2])
{
	if (cmd->index + 1 != data(GET)->cmd_amount)
	{
		ft_close(pipe_fd[RD]);
		redirect(pipe_fd[WR], STDOUT_FILENO);
	}
	else
		redirect(data(GET)->stdout_copy, STDOUT_FILENO);
	if (!cmd_apply_redirs(cmd))
		minishell_exit(1, NULL);
	if (execve(cmd->bin, cmd->argv, NULL))
		minishell_exit(0, NULL);
}

static int	cmd_execute(t_cmd *cmd)
{
	int		pipe_fd[2];

	dprintf(STDERR_FILENO, "Executing: %s[%d]\n", cmd->name, cmd->index);
	cmd_heredoc_run(cmd);
	if (!cmd->redir_valid)
		return (0);
	if (cmd->index + 1 != data(GET)->cmd_amount && pipe(pipe_fd) == -1)
		minishell_exit(1, NULL);
	cmd->pid = fork();
	if (cmd->pid == -1)	
	{
		if (cmd->index + 1 != data(GET)->cmd_amount)
		{
			ft_close(pipe_fd[RD]);
			ft_close(pipe_fd[WR]);
		}
		minishell_exit(1, NULL);
	}
	if (cmd->pid == 0)
		cmd_execute_child(cmd, pipe_fd);
	if (cmd->index + 1 != data(GET)->cmd_amount)
	{
		ft_close(pipe_fd[WR]);
		redirect(pipe_fd[RD], STDIN_FILENO);
	}
	return (1);
}

void	executor(void)
{
	int	i;
	int	status;

	i = 0;
	dprintf(STDERR_FILENO, "Executor\n");
	dprintf(STDERR_FILENO, "Amount of commands: %d\n", data(GET)->cmd_amount);
	while (i < data(GET)->cmd_amount)
	{
		if (!cmd_execute(data(GET)->commands[i]))
			break ;
		i++;
	}
	if (waitpid(data(GET)->commands[data(GET)->cmd_amount - 1]->pid, &status, 0) == -1)
		minishell_exit(1, NULL);
	if (WIFEXITED(status))
		data(GET)->exit_code = WEXITSTATUS(status);
	commands_reset();
	stdfd_reset();
}
