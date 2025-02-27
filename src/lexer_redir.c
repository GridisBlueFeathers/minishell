/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:07 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 17:00:08 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_double_redir_check(char *prompt)
{
	char	redir;

	redir = prompt[0];
	if (!prompt[1])
		return (lexer_error('\n', 0), 0);
	if (prompt[1] != redir)
	{
		if (isredir(prompt[1]) || prompt[1] == '|')
			return (lexer_error(prompt[1], 0), 0);
		else
			return (1);
	}
	if (prompt[2] && isredir(prompt[2]))
	{
		if (prompt[3] && prompt[3] == prompt[2])
			return (lexer_error(prompt[2], prompt[3]), 0);
		else
			return (lexer_error(prompt[2], 0), 0);
	}
	return (1);
}

static int	lexer_redir_check_last(char *prompt)
{
	size_t	i;
	char	last;

	i = 1;
	last = prompt[0];
	if (isredir(prompt[1]))
		i = 2;
	while (isspace(prompt[i]))
		i++;
	if (!prompt[i])
		return (lexer_error('\n', 0), 0);
	else if (isredir(prompt[i]) && prompt[i + 1] == prompt[i])
		return (lexer_error(prompt[i], prompt[i + 1]), 0);
	else if (isredir(prompt[i]))
		return (lexer_error(prompt[i], 0), 0);
	else if (prompt[i] == '|')
		return (lexer_error(prompt[i], 0), 0);
	return (1);
}

int	lexer_redir_check(void)
{
	size_t	i;

	i = 0;
	if (!ft_strchr(data(GET)->rl_prompt, '<')
		&& !ft_strchr(data(GET)->rl_prompt, '>'))
		return (1);
	while (data(GET)->rl_prompt[i])
	{
		if (isredir(data(GET)->rl_prompt[i])
			&& valid_operator(data(GET)->rl_prompt, i, 0))
		{
			if (!lexer_double_redir_check(data(GET)->rl_prompt + i))
				return (0);
			if (!lexer_redir_check_last(data(GET)->rl_prompt + i))
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}
