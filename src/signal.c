/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:25:48 by svereten          #+#    #+#             */
/*   Updated: 2025/02/26 17:35:22 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <errno.h>

void	signal_int(int signal)
{
	(void)signal;
	data(GET)->exit_code = 130;
	if (data(GET)->mode != IN_EXECUTION)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
		ft_putchar_fd('\n', STDOUT_FILENO);
	data(GET)->mode = IN_PROMPT;
	return ;
}

void	signal_pipe(int	signal)
{
	(void)signal;
	if (errno == EPIPE)
		errno = 0;
	minishell_exit(1, NULL);
}

void	signal_init(void)
{
	struct sigaction	action;

	action.sa_handler = signal_int;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	sigaction(SIGINT, &action, NULL);
	signal(SIGQUIT, SIG_IGN);
}
