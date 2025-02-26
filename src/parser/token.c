/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:56:27 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:56:29 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*token_allocate(t_prompt *prompt)
{
	t_token	*node;

	node = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!node)
		minishell_exit(1, NULL);
	node->tok_str = NULL;
	node->tok_type = 0;
	node->next = NULL;
	if (!data(GET)->prompt[prompt->idx]->last)
	{
		data(GET)->prompt[prompt->idx]->first = node;
		data(GET)->prompt[prompt->idx]->last = node;
	}
	else
	{
		data(GET)->prompt[prompt->idx]->last->next = node;
		data(GET)->prompt[prompt->idx]->last = node;
	}
	return (node);
}

static size_t	token_redir_set(t_token *token)
{
	if (token->tok_type == APPEND)
	{
		token->tok_str = ft_strdup(">>");
		if (!token->tok_str)
			minishell_exit(1, NULL);
	}
	if (token->tok_type == HEREDOC)
	{
		token->tok_str = ft_strdup("<<");
		if (!token->tok_str)
			minishell_exit(1, NULL);
	}
	if (token->tok_type == OUTPUT)
	{
		token->tok_str = ft_strdup(">");
		if (!token->tok_str)
			minishell_exit(1, NULL);
	}
	if (token->tok_type == INPUT)
	{
		token->tok_str = ft_strdup("<");
		if (!token->tok_str)
			minishell_exit(1, NULL);
	}
	return (ft_strlen(token->tok_str) - 1);
}

static size_t	token_str_set(char *prompt, t_token *token)
{
	if (token->tok_type == WORD)
	{
		token->tok_str = ft_substr(prompt, 0, wordlen(prompt));
		if (!token->tok_str)
			minishell_exit(1, NULL);
		return (wordlen(prompt) - 1);
	}
	return (token_redir_set(token));
}

static t_tok_type	token_type_set(char *prompt, size_t loc)
{
	if (!prompt)
		return (EOP);
	if (isredir(prompt[loc]) && prompt[loc + 1] && isredir(prompt[loc + 1])
		&& valid_operator(prompt, loc, 0))
	{
		if (prompt[loc + 1] == '>')
			return (APPEND);
		else if (prompt[loc + 1] == '<')
			return (HEREDOC);
	}
	else if (isredir(prompt[loc]) && !isredir(prompt[loc + 1])
		&& valid_operator(prompt, loc, 0))
	{
		if (prompt[loc] == '>')
			return (OUTPUT);
		else
			return (INPUT);
	}
	return (WORD);
}

void	token_init(t_prompt *prompt)
{
	int		i;
	int		idx;
	t_token	*token;

	i = 0;
	idx = 0;
	while (prompt->name[i])
	{
		if (isspace(prompt->name[i]))
		{
			i++;
			continue ;
		}
		token = token_allocate(prompt);
		token->tok_type = token_type_set(prompt->name, i);
		i += token_str_set(prompt->name + i, token);
		token->idx = idx;
		i++;
		idx++;
	}
}
