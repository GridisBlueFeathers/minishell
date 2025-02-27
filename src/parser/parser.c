/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:51:25 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:00:14 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void	parser_cleanup(void)
{
	size_t	i;
	t_token	*token;
	t_token	*last;

	i = 0;
	if (!data(GET)->prompt)
		return ;
	while (data(GET)->prompt[i])
	{
		token = data(GET)->prompt[i]->first;
		while (token)
		{
			last = token;
			token = token->next;
			ft_free(STR, &last->tok_str);
			ft_free(STRUCT, &last);
		}
		ft_free(STR, &data(GET)->prompt[i]->name);
		ft_free(STRUCT, &data(GET)->prompt[i]);
		i++;
	}
	ft_free(STRUCT, &data(GET)->prompt);
}

void	parser(void)
{
	size_t		i;

	i = 0;
	prompt_init();
	while (data(GET)->prompt[i])
	{
		data(GET)->prompt[i]->idx = i;
		expander_init(data(GET)->prompt[i]);
		token_init(data(GET)->prompt[i]);
		quotes_rm_init(data(GET)->prompt[i]->first);
		i++;
	}
	command_table_init();
	parser_cleanup();
}
