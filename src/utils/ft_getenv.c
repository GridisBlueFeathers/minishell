/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:01:29 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/30 21:35:42 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *key)
{
	t_env_var	*var;

	var = data(GET)->env.first;
	while (var)
	{
		if (!ft_strncmp(key, var->key, ft_strlen(key)))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

t_env_var	*ft_getenv_node(char *key)
{
	t_env_var	*res;

	res = data(GET)->env.first;
	while (res)
	{
		if (!ft_strncmp(key, res->key, ft_strlen(key)))
			return (res);
		res = res->next;
	}
	return (res);
}

t_env_var	*ft_get_alloc_env_node(char *key)
{
	t_env_var	*res;

	res = ft_getenv_node(key);
	if (!res)
	{
		res = env_allocate();
		res->key = ft_strdup(key);
		if (!res->key)
			minishell_exit(1, NULL);
	}
	return (res);
}
