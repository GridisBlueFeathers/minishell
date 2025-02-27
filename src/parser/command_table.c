/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:17 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:08:09 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_table_allocate(int idx)
{
	t_cmd	*command;

	command = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!command)
		minishell_exit(1, NULL);
	data(GET)->commands[idx] = command;
	command->pid = 1;
	command->idx = idx;
	command->type = -1;
}

static void	command_table_set(int idx)
{
	t_token	*token;

	command_table_allocate(idx);
	token = data(GET)->prompt[idx]->first;
	while (token)
	{
		if (token->tok_type > 1 && token->tok_type < 7)
		{
			redir_set(token, idx);
			token = token->next->next;
			continue ;
		}
		if (token->tok_type == CMD)
			data(GET)->commands[idx]->name = ft_strdup(token->tok_str);
		if (!data(GET)->commands[idx]->name)
			minishell_exit(1, NULL);
		if (token->tok_type == CMD && is_builtin(token->tok_str))
			data(GET)->commands[idx]->type = BUILTIN;
		token = token->next;
	}
	if (data(GET)->commands[idx]->type != BUILTIN)
		data(GET)->commands[idx]->type = BIN;
}

static void	command_type_get(t_token *token)
{
	int	first_word;

	first_word = 1;
	while (token)
	{
		if (token->tok_type > 1 && token->tok_type < 7)
			token = token->next;
		else if (token->tok_type == WORD && first_word)
		{
			token->tok_type = CMD;
			first_word = 0;
		}
		if (!token->next)
			break ;
		token = token->next;
	}
}

void	command_table_init(void)
{
	int	i;

	i = 0;
	while (data(GET)->prompt[i])
		i++;
	data(GET)->cmd_amount = i;
	data(GET)->commands = (t_cmd **)ft_calloc(i + 1, sizeof(t_cmd *));
	if (!data(GET)->commands)
		minishell_exit(1, NULL);
	i = 0;
	while (data(GET)->prompt[i])
	{
		command_type_get(data(GET)->prompt[i]->first);
		command_table_set(i);
		ct_argv_set(data(GET)->prompt[i]);
		i++;
	}
}
