/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:25:48 by svereten          #+#    #+#             */
/*   Updated: 2024/11/27 18:33:58 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/stdio.h"
#include "minishell.h"
#include <readline/readline.h>

void	signal_int(int signal)
{
	(void)signal;
	data(GET)->exit_code = 130;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	printf("Kill all children instead of this please\n");
	rl_on_new_line();
	rl_redisplay();
	return ;
}
