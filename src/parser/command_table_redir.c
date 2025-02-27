/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:36 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:08:24 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*redir_allocate(int idx)
{
	t_redir	*redir;

	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
		minishell_exit(1, NULL);
	if (!data(GET)->commands[idx]->redir_head)
	{
		data(GET)->commands[idx]->redir_head = redir;
		data(GET)->commands[idx]->redir_tail = redir;
	}
	else
	{
		data(GET)->commands[idx]->redir_tail->next = redir;
		data(GET)->commands[idx]->redir_tail = redir;
	}
	return (redir);
}

void	redir_set(t_token *token, int idx)
{
	t_redir	*redir;

	redir = redir_allocate(idx);
	redir->type = token->tok_type;
	redir->file_name = ft_strdup(token->next->tok_str);
	if (!redir->file_name)
		minishell_exit(1, NULL);
	if (redir->type == HEREDOC || redir->type == HRDC_EXPND)
		redir->heredoc_delim = ft_strdup(redir->file_name);
	if (redir->type == HRDC_EXPND)
		redir->heredoc_expand = 1;
	else
		redir->heredoc_expand = 0;
}
