/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:01:06 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:10:44 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

void	signal_pipe(int signal)
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
