/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:25:17 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/27 15:03:44 by jwolfram         ###   ########.fr       */
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

static t_env_var	*env_allocate(void)
{
	t_env_var	*node;

	node = (t_env_var *)ft_calloc(1, sizeof(t_env_var));
	if (!node)
		minishell_exit(1, NULL);
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
	}
	return (node);
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
