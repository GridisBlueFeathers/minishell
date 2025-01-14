/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:00:20 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/14 17:46:31 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_table_set(int idx)
{
	t_token *token;

	token = data(GET)->prompt[idx]->first;
	while (token)
	{
		if (token->tok_type > 1 && token->tok_type < 6)
		{
			redir_allocate(idx);
			token = token->next->next;
			continue ;
		}
		if (token->tok_type == CMD)
			data(GET)->commands[idx]->name = token->tok_str;
		if (is_builtin(token->tok_str))
			data(GET)->commands[idx]->type = BUILTIN;
		token = token->next;
	}
	if (data(GET)->commands[idx]->type == -1)
		data(GET)->commands[idx]->type = BIN;
}

static void	command_table_allocate(int idx)
{
	data(GET)->commands[idx] = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (data(GET)->commands[idx])
		minishell_exit(1, NULL);
	data(GET)->commands[idx]->name = NULL;
	data(GET)->commands[idx]->bin = NULL;
	data(GET)->commands[idx]->argv = NULL;
	data(GET)->commands[idx]->type = -1;
	data(GET)->commands[idx]->redir_head = NULL;
	data(GET)->commands[idx]->redir_tail = NULL;
}

static void	command_type_get(t_token *token)
{
	int	first_word;

	first_word = 1;
	while (token)
	{
		if (token->tok_type > 1 && token->tok_type < 6)
		{
			token = token->next->next;
			continue ;
		}
		else if (token->tok_type == WORD && first_word)
		{
			token->tok_type = CMD;
			first_word = 0;
		}
		token = token->next;
	}
}

void	command_table_init(void)
{
	int	i;

	i = 0;
	while (data(GET)->prompt[i])
		i++;
	data(GET)->cmd_amount = i + 1;
	data(GET)->commands = (t_cmd **)ft_calloc(i + 2, sizeof(t_cmd *));
	if (data(GET)->commands)
		minishell_exit(1, NULL);
	i = 0;
	while (data(GET)->prompt[i])
	{
		command_table_allocate(i);
		command_table_set(i);
		if (data(GET)->commands[i]->redir_head)
			redir_struct_init(data(GET)->prompt[i]);
		argv_init(data(GET)->prompt[i]);
		i++;
	}
}
