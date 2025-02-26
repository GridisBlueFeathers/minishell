/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:56:50 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:56:52 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *key)
{
	t_env_var	*var;

	var = data(GET)->env.first;
	while (var)
	{
		if (!ft_strcmp(key, var->key))
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
		if (!ft_strcmp(key, res->key))
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
