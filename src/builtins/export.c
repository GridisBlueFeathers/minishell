/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:45:52 by svereten          #+#    #+#             */
/*   Updated: 2025/01/31 14:27:07 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"
#include "command.h"
#include <stdio.h>

/**
 * "declare -x " strlen is 11 + '\n' makes 12
 * 3 additional characters for =""
 */
static size_t	export_get_len(void)
{
	t_env_var	*cur;
	size_t		len;

	len = 0;
	cur = data(GET)->env.first;
	while (cur)
	{
		if (cur->was_unset)
		{
			cur = cur->next;
			continue ;
		}
		len += ft_strlen(cur->key) + 12;
		if (cur->value)
			len += ft_strlen(cur->value) + 3;
		cur = cur->next;
	}
	return (len);
}

static char	*export_get_output(void)
{
	t_env_var	*cur;
	char		*output;
	size_t		len;

	len = export_get_len();
	output = (char *)ft_calloc(len + 1, sizeof(char));
	if (!output)
		minishell_exit(1, NULL);
	cur = data(GET)->env.first;
	while (cur)
	{
		if (cur->was_unset)
		{
			cur = cur->next;
			continue ;
		}
		ft_strlcat(output, "declare -x ", len + 1);
		ft_strlcat(output, cur->key, len + 1);
		if (cur->value)
		{
			ft_strlcat(output, "=\"", len + 1);
			ft_strlcat(output, cur->value, len + 1);
			ft_strlcat(output, "\"", len + 1);
		}
		ft_strlcat(output, "\n", len + 1);
		cur = cur->next;
	}
	return (output);
}

static int	export_no_args(void)
{
	char	*output;

	output = export_get_output();
	if (ft_putstr_fd(output, STDOUT_FILENO) < 0)
		minishell_exit(1, NULL);
	return (0);
}

int	builtin_export(t_cmd *cmd)
{
	int			i;
	char		*eq_sign_loc;
	char		*key;
	t_env_var	*node;

	if (!cmd->argv[1])
		return (export_no_args());
	i = 1;
	while (cmd->argv[i])
	{
		eq_sign_loc = ft_strchr(cmd->argv[i], '=');
		if (!eq_sign_loc)
			ft_get_alloc_env_node(cmd->argv[i]);
		else
		{
			key = ft_substri(cmd->argv[i], 0, eq_sign_loc - cmd->argv[i]);
			if (!key)
				minishell_exit(1, NULL);
			node = ft_get_alloc_env_node(key);
			node->value = ft_substri(cmd->argv[i], eq_sign_loc - cmd->argv[i], ft_strlen(cmd->argv[i]) - 1);
			ft_free(STR, &key);
		}
		i++;
	}
	return (0);
}
