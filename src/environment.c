/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:25:17 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/19 17:11:15 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
}

t_env_cont	*allocate_env(void)
{
	t_env_cont	*content;

	content = (t_env_cont *)ft_calloc(1, sizeof(t_env_cont));
	if (!content)
		ft_panic(1, NULL);
	content->next = NULL;
	content->prev = NULL;
	return (content);
}

void	env_init(char **env)
{
	t_env_cont	*content;
	int			i;

	if (!env)
		ft_panic(1, "Environment not found");
	i = 0;
	while(env[i])
	{
		content = allocate_env();
		if (!content)
			ft_panic(1, NULL);
		if (!data(GET)->env.last)
			data(GET)->env.first = content;
		else
		{
			data(GET)->env.last->next = content;
			content->prev = data(GET)->env.last;
		}
		data(GET)->env.last = content;
		content->key = ft_substr(env[i], 0, ft_strchr(env[i], '=') - env[i]);
		content->value = ft_substr(env[i], ft_strchr(env[i], '=') - env[i] + 1, ft_strlen(env[i]));
		i++;
	}
}
