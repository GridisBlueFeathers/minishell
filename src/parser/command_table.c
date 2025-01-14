/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:00:20 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/10 17:08:12 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_table_init(t_token *token)
{
	int	first_word;
 
	first_word = 0;
	while (token)
	{
		if (token->tok_type == WORD && !first_word)
	}
}
