/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:47:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 13:29:58 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	ct_argv_set(t_prompt *prompt)
{
	int		i;
	t_token	*token;
	t_data	*ms_data;

	if (!prompt->last)
		return ;
	ms_data = data(GET);
	ms_data->commands[prompt->idx]->argv
		= (char **)ft_calloc(prompt->last->idx + 2, sizeof(char *));
	if (!data(GET)->commands[prompt->idx]->argv)
		minishell_exit(1, NULL);
	token = prompt->first;
	i = 0;
	while (token)
	{
		if (token->tok_type > 1 && token->tok_type < 7)
			token = token->next;
		else if (token->tok_type == WORD || token->tok_type == CMD)
		{
			ms_data->commands[prompt->idx]->argv[i] = ft_strdup(token->tok_str);
			if (!data(GET)->commands[prompt->idx]->argv[i])
				minishell_exit(1, NULL);
			i++;
		}
		token = token->next;
	}
}
