/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:34:06 by jwolfram          #+#    #+#             */
/*   Updated: 2024/12/13 17:02:19 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/stdio.h"
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
	if (token->tok_type ==OUTPUT)
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

static t_tok_type	token_type_set(char *prompt)
{
	if (!prompt)
		return (EOP);
	if (isredir(prompt[0]) && prompt[1] && isredir(prompt[1]))
	{
		if (prompt[1] == '>')
			return (APPEND);
		else if (prompt[1] == '<')
				return (HEREDOC);
	}
	else if (isredir(prompt[0]) && prompt[1] && !isredir(prompt[1]))
	{
		if (prompt[0] == '>')
			return (OUTPUT);
		else
			return (INPUT);
	}
	return (WORD);
}

static void	token_init(t_prompt *prompt)
{
	int		i;
	t_token	*token;

	i = 0;
	while (prompt->name[i])
	{
		if (isspace(prompt->name[i]))
		{
			i++;
			continue ;
		}
		token = token_allocate(prompt);
		token->tok_type = token_type_set(prompt->name + i);
		i += token_str_set(prompt->name + i, token);
		i++;
	}
}

void	prompt_init(void)
{
	char	**prompt;
	int		len;
	int		i;

	prompt = minishell_split(data(GET)->rl_prompt);
	ft_putstrarr_fd(prompt, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (!prompt)
		minishell_exit(1, NULL);
	i = 0;
	len = ft_strarrlen(prompt);
	data(GET)->prompt = (t_prompt **)ft_calloc(len + 1, sizeof(t_prompt *));
	if (!data(GET)->prompt)
		minishell_exit(1, NULL);
	while (i < len)	
	{
		data(GET)->prompt[i] = (t_prompt *)ft_calloc(1, sizeof(t_prompt));
		if (!data(GET)->prompt[i])
			minishell_exit(1, NULL);
		data(GET)->prompt[i]->name = prompt[i];
		data(GET)->prompt[i]->idx = i;
		i++;
	}
}

void	parser_init(void)
{
	size_t		i;

	i = 0;
	prompt_init();
	while (data(GET)->prompt[i])
	{
		data(GET)->prompt[i]->idx = i;
		token_init(data(GET)->prompt[i]);
		i++;
	}

}
