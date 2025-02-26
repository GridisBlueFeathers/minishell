/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:59:59 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 17:00:00 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_quote_check(void)
{
	size_t	i;
	char	quote;

	i = 0;
	quote = 0;
	while (data(GET)->rl_prompt[i])
	{
		if (data(GET)->rl_prompt[i] == '\\' && data(GET)->rl_prompt[i + 1]
			&& isquote(data(GET)->rl_prompt[i + 1]))
			i += 2;
		if (!quote)
		{
			if (isquote(data(GET)->rl_prompt[i]))
				quote = data(GET)->rl_prompt[i];
		}
		else if ((quote == '\'' && data(GET)->rl_prompt[i] == '\'')
			|| (quote == '"' && data(GET)->rl_prompt[i] == '"'))
			quote = 0;
		i++;
	}
	if (quote)
		return (lexer_error(quote, 0), 0);
	return (1);
}

static int	lexer_pipe_check(void)
{
	size_t	i;
	t_data	*dt;

	i = 0;
	dt = data(GET);
	if (!ft_strchr(dt->rl_prompt, '|'))
		return (1);
	while (ft_isspace(dt->rl_prompt[i]))
		i++;
	if (dt->rl_prompt[i] == '|' && valid_operator(dt->rl_prompt, i, 0))
		return (lexer_error('|', 0), 0);
	while (dt->rl_prompt[i])
	{
		if (dt->rl_prompt[i] == '|')
		{
			i++;
			while (ft_isspace(dt->rl_prompt[i]))
				i++;
			if (!dt->rl_prompt[i] || (dt->rl_prompt[i] == '|'
					&& valid_operator(dt->rl_prompt, i, 0)))
				return (lexer_error('|', 0), 0);
		}
		i++;
	}
	return (1);
}

void	lexer_error(char error, char redir)
{
	if (error == '|')
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (error == '\n')
		ft_putstr_fd(NL_ERROR, 2);
	else if (error == '\'')
		ft_putstr_fd("minishell: syntax error near unexpected token `\''\n", 2);
	else if (error == '"')
		ft_putstr_fd("minishell: syntax error near unexpected token `\"'\n", 2);
	else if (error == '<' && !redir)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (error == '>' && !redir)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (error == '<' && error == redir)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (error == '>' && error == redir)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
}

int	lexer(void)
{
	if (str_isspace(data(GET)->rl_prompt))
		return (0);
	if (!lexer_quote_check())
	{
		data(GET)->exit_code = 2;
		return (0);
	}
	if (!lexer_pipe_check())
	{
		data(GET)->exit_code = 2;
		return (0);
	}
	if (!lexer_redir_check())
	{
		data(GET)->exit_code = 2;
		return (0);
	}
	return (1);
}
