/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:15:02 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/06 16:58:25 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_exec(void)
{
	if (!data(GET)->rl_prompt[0])
		return ;
	add_history(data(GET)->rl_prompt);
	if (!ft_strcmp(data(GET)->rl_prompt, "cat Makefile"))
		dev_mock_cat_make();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat << hey"))
		dev_mock_cat_heredoc();	
	if (!ft_strcmp(data(GET)->rl_prompt, "echo hi"))
		dev_mock_echo_hi();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat dev/2 | grep hey | wc -l"))
		dev_mock_cat_pipe_grep_pipe_wc();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat dev/2 | grep hey"))
		dev_mock_cat_pipe_grep();	
	if (!ft_strcmp(data(GET)->rl_prompt, "cat dev/2"))
		dev_mock_cat_dev2();	
	printf("Prompt: %s\n", data(GET)->rl_prompt);
	if (!lexer())
		return ;
	executor();
	data(GET)->exit_code = 0;
}

void	loop(void)
{
	signal_init();
	while (1)
	{
		if (data(GET)->exit_code)
			data(GET)->rl_prompt = readline(PREFIX_BAD);
		else
			data(GET)->rl_prompt = readline(PREFIX_GOOD);
		if (!data(GET)->rl_prompt)
			minishell_exit(0, NULL);
		prompt_exec();
		free(data(GET)->rl_prompt);
	}
}
