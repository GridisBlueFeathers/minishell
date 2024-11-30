/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:25:17 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/27 15:25:13 by svereten         ###   ########.fr       */
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
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

static void	env_set(char **env)
{
	int			i;
	int			len;
	t_env_var	*node;

	i = 0;
	node = data(GET)->env.first;
	while (env[i])
	{
		len = ft_strchr(env[i], '=') - env[i];
		node->key = ft_substr(env[i], 0, len);
		if (!node->key)
			minishell_exit(1, NULL);
		node->value = ft_substr(env[i], len + 1, ft_strlen(env[i]));
		if (!node->value)
			minishell_exit(1, NULL);
		if (!env[i + 1])
			break ;
		node = env_allocate();
		data(GET)->env.last->next = node;
		node->prev = data(GET)->env.last;
		data(GET)->env.last = node;
		i++;
	}
}

void	env_init(char **env)
{
	t_env_var	*node;
	int			fd;

	node = env_allocate();
	data(GET)->env.first = node;
	data(GET)->env.last = node;
	if (!env[0])
	{
		fd = -1;
		node->key = ft_strdup("USER");
		if (!node->key)
			minishell_exit(1, NULL);
		/* if needed add function that finds username */
		node->value = ft_strdup("Han is cool and always gay");
		if (!node->value)
			minishell_exit(1, NULL);
	}
	else
	{
		env_set(env);
		path_set();
	}
}
