/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:25:48 by svereten          #+#    #+#             */
/*   Updated: 2025/01/23 16:12:23 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include <sys/ioctl.h>

void	signal_int(int signal)
{
	(void)signal;
	data(GET)->exit_code = 130;
	data(GET)->mode = IN_PROMPT;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	return ;
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
