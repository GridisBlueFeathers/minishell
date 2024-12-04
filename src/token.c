/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:34:06 by jwolfram          #+#    #+#             */
/*   Updated: 2024/12/04 18:48:07 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*token_allocate(void)
{
	t_token	*node;

	node = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!node)
		minishell_exit(1, NULL);
	node->tok_str = NULL;
	node->tok_type = 0;
	node->next = NULL;
	return (node);
}

static void	token_set_var(char *token, t_tok_type type)
{
	if (type = APPEND)
	{

	}
}

static void	token_set(char *prompt)
{
	if (!prompt)
		return ;
	if (isredir(prompt[0]) && prompt[1] && isredir(prompt[1]))
	{
		if (prompt[1] == '>')
			token_set_var(prompt, APPEND);
		else if (prompt[1] == '<')
			token_set_var(prompt, HEREDOC);
	}
	else if (isredir(prompt[0]) && prompt[1] && !isredir(prompt[1]))
	{
		if (prompt[0] == '>')
			token_set_var(prompt, OUTPUT);
		else
			token_set_var(prompt, INPUT);
	}
	else if (!isredir(prompt[0]))
		token_set_var(prompt, WORD);
}

static void	token_init(char *prompt)
{
	int		i;
	t_token	*token;

	i = 0;
	token = token_allocate();
	data(GET)->prompt[i]->first = token;
	data(GET)->prompt[i]->last = token;
	while ()
	{
		token_set(prompt + i);
		if (!prompt[i + 1])
			break ;
		token = token_allocate();
		data(GET)->prompt[i]->last->next = token;
		data(GET)->prompt[i]->last = token;
	}
}

void	prompt_init(void)
{
	char	**prompt;
	int		len;
	int		i;

	prompt = ft_split(data(GET)->rl_prompt, '|');
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
		token_init(data(GET)->prompt[i]->name);
		i++;
	}

}
