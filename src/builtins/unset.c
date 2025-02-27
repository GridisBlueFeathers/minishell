/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:39:35 by svereten          #+#    #+#             */
/*   Updated: 2025/02/27 12:48:07 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	builtin_unset(t_cmd *cmd)
{
	int			i;
	t_env_var	*node;

	if (!cmd->argv[1])
		return (0);
	i = 1;
	while (cmd->argv[i])
	{
		node = ft_getenv_node(cmd->argv[i]);
		if (!node)
			return (0);
		ft_free(STR, &node->value);
		node->was_unset = 1;
		i++;
	}
	return (0);
}
