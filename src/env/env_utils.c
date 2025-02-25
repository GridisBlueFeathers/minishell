/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 14:13:56 by svereten          #+#    #+#             */
/*   Updated: 2025/02/25 14:15:20 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_free(t_env_var	*node)
{
	t_env_var	*tmp;

	while (node)
	{
		ft_free(STR, &node->key);
		ft_free(STR, &node->value);
		tmp = node->next;
		ft_free(STRUCT, &node);
		node = tmp;
	}
}

t_env_var	*env_allocate(void)
{
	t_env_var	*node;

	node = (t_env_var *)ft_calloc(1, sizeof(t_env_var));
	if (!node)
		minishell_exit(1, NULL);
	node->was_unset = 0;
	if (!data(GET)->env.first)
	{
		data(GET)->env.first = node;
		data(GET)->env.last = node;
	}
	else
	{
		data(GET)->env.last->next = node;
		node->prev = data(GET)->env.last;
		data(GET)->env.last = node;
		node->idx = node->prev->idx + 1;
	}
	return (node);
}
