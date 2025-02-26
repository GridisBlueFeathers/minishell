/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:28 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:55:30 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ct_argv_allocate(t_prompt *prompt)
{
	t_cmd	**cmd;

	cmd = data(GET)->commands;
	cmd[prompt->idx]->argv
		= (char **)ft_calloc(prompt->last->idx + 2, sizeof(char *));
	if (!cmd[prompt->idx]->argv)
		minishell_exit(1, NULL);
}

void	ct_argv_set(t_prompt *prompt)
{
	int		i;
	t_token	*token;

	if (!prompt->last)
		return ;
	ct_argv_allocate(prompt);
	token = prompt->first;
	i = 0;
	while (token)
	{
		if (token->tok_type > 1 && token->tok_type < 7)
			token = token->next;
		else if (token->tok_type == WORD || token->tok_type == CMD)
		{
			data(GET)->commands[prompt->idx]->argv[i]
			= ft_strdup(token->tok_str);
			if (!data(GET)->commands[prompt->idx]->argv[i])
				minishell_exit(1, NULL);
			i++;
		}
		token = token->next;
	}
}
