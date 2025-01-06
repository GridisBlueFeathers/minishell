/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:08:58 by svereten          #+#    #+#             */
/*   Updated: 2025/01/06 17:53:50 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void	executor(void)
{
	int	i;
	int	s;

	i = 0;
	dprintf(STDERR_FILENO, "Executor\n");
	dprintf(STDERR_FILENO, "Amount of commands: %d\n", data(GET)->cmd_amount);
	data(GET)->mode = IN_HEREDOC;
	while (data(GET)->commands[i])
	{
		if (!cmd_heredoc_run(data(GET)->commands[i]))
		{
			commands_reset();
			return ;
		}
		i++;
	}
	i = 0;
	while (i < data(GET)->cmd_amount)
	{
		if (!cmd_execute(data(GET)->commands[i]))
			break ;
		i++;
	}
	if (waitpid(data(GET)->commands[data(GET)->cmd_amount - 1]->pid, &s, 0) == -1)
		minishell_exit(1, NULL);
	if (WIFEXITED(s))
		data(GET)->exit_code = WEXITSTATUS(s);
	commands_reset();
	stdfd_reset();
}
