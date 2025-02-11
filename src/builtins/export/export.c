/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:30:17 by svereten          #+#    #+#             */
/*   Updated: 2025/02/10 17:19:16 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	export_new_var(char *arg, int eq_index)
{
	char		*key;
	t_env_var	*node;

	key = ft_substri(arg, 0, eq_index - 1);
	if (!key)
		minishell_exit(1, NULL);
	node = ft_get_alloc_env_node(key);
	if (node->value)
		ft_free(STR, &node->value);
	node->value = ft_substri(arg, eq_index + 1, ft_strlen(arg) - 1);
	ft_free(STR, &key);
}

int	builtin_export(t_cmd *cmd)
{
	int			i;
	char		*eq_sign_loc;

	if (!cmd->argv[1])
		return (builtin_export_no_args());
	i = 1;
	while (cmd->argv[i])
	{
		eq_sign_loc = ft_strchr(cmd->argv[i], '=');
		if (!eq_sign_loc)
			ft_get_alloc_env_node(cmd->argv[i]);
		else
			export_new_var(cmd->argv[i], eq_sign_loc - cmd->argv[i]);
		i++;
	}
	return (0);
}
