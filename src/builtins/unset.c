/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:53:31 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:06:36 by svereten         ###   ########.fr       */
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
