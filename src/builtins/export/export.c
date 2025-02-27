/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:51:58 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:06:05 by svereten         ###   ########.fr       */
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

static int	export_error_id(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (1);
}

/**
 * check: if alphabetic or underscore character was found yet
 */
static int	export_check_key(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (!check && (ft_isalpha(str[i]) || str[i] == '_'))
			check = 1;
		if (!check && ft_isdigit(str[i]))
			return (1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	if (ft_isnumber(str))
		return (1);
	return (0);
}

static int	export_check_arg(char *str, char *eq)
{
	int		idx;
	int		err;
	char	*key;

	if (!eq)
		err = export_check_key(str);
	else
	{
		if (eq == str)
			return (1);
		idx = eq - str - 1;
		key = ft_substri(str, 0, idx);
		if (!key)
			minishell_exit(1, NULL);
		err = export_check_key(key);
		ft_free(STR, &key);
	}
	return (err);
}

int	builtin_export(t_cmd *cmd)
{
	int			i;
	int			error;
	char		*eq_sign_loc;

	if (!cmd->argv[1])
		return (builtin_export_no_args());
	i = 1;
	error = 0;
	while (cmd->argv[i])
	{
		eq_sign_loc = ft_strchr(cmd->argv[i], '=');
		error = export_check_arg(cmd->argv[i], eq_sign_loc);
		if (error)
		{
			export_error_id(cmd->argv[i]);
			i++;
			continue ;
		}
		if (!eq_sign_loc)
			ft_get_alloc_env_node(cmd->argv[i]);
		else
			export_new_var(cmd->argv[i], eq_sign_loc - cmd->argv[i]);
		i++;
	}
	return (error);
}
