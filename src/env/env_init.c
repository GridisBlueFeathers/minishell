/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:25:17 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 14:27:16 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/stdlib.h"
#include "libft/string.h"
#include "minishell.h"

static char *handle_shlvl(char *var)
{
	char	*res;
	int		eq_loc;

	eq_loc = ft_strchr(var, '=') - var;
	if (!ft_isnumber(&var[eq_loc + 1]))
		return (ft_strdup("1"));
	res = ft_itoa(ft_atoi(&var[eq_loc + 1]) + 1);
	return (res);
}

static void	env_set(char **env)
{
	int			i;
	int			len;
	t_env_var	*node;

	i = 0;
	while (env[i])
	{
		node = env_allocate();
		len = ft_strchr(env[i], '=') - env[i];
		node->key = ft_substr(env[i], 0, len);
		if (!node->key)
			minishell_exit(1, NULL);
		if (ft_strcmp(node->key, "SHLVL") == 0)
			node->value = handle_shlvl(env[i]);
		else
			node->value = ft_substr(env[i], len + 1, ft_strlen(env[i]));
		if (!node->value)
			minishell_exit(1, NULL);
		node->idx = i;
		if (!env[i + 1])
			break ;
		i++;
	}
}

static void	no_env_set(void)
{
	t_env_var	*node;

	node = env_allocate();
	node->key = ft_strdup("OLDPWD");
	if (!node->key)
		minishell_exit(1, NULL);
	node = env_allocate();
	node->key = ft_strdup("PWD");
	if (!node->key)
		minishell_exit(1, NULL);
	node->value = getcwd(NULL, 0);
	if (!node->value)
		minishell_exit(1, NULL);
	node->idx = 0;
	node = env_allocate();
	node->key = ft_strdup("SHLVL");
	if (!node->key)
		minishell_exit(1, NULL);
	node->value = ft_strdup("1");
	if (!node->value)
		minishell_exit(1, NULL);
	node->idx = 1;
}

void	env_init(char **env)
{
	if (!env[0])
		no_env_set();
	else
	{
		env_set(env);
		path_set();
	}
}
