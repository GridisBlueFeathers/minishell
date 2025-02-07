/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:47:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/07 13:08:15 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"
#include "minishell.h"
#include <stdio.h>

void	ct_argv_set(t_prompt *prompt)
{
	int		i;
	t_token	*token;
	t_data	*ms_data;

	ms_data = data(GET);
	ms_data->commands[prompt->idx]->argv
		= (char **)ft_calloc(prompt->last->idx + 2, sizeof(char *));
	if (!data(GET)->commands[prompt->idx]->argv)
		minishell_exit(1, NULL);
	token = prompt->first;
	i = 0;
	while (token)
	{
		if (token->tok_type > 1 && token->tok_type < 7)
			token = token->next;
		else if (token->tok_type == WORD || token->tok_type == CMD)
		{
			ms_data->commands[prompt->idx]->argv[i] = ft_strdup(token->tok_str);
			if (!data(GET)->commands[prompt->idx]->argv[i])
				minishell_exit(1, NULL);
			i++;
		}
		token = token->next;
	}
}

static void	ct_env_set_var(t_env_var *var, int i)
{
	size_t	len;

	len = ft_strlen(var->key) +  ft_strlen(var->value) + 1;
	data(GET)->env_arr[i] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!data(GET)->env_arr[i])
		minishell_exit(1, NULL);
	ft_strlcat(data(GET)->env_arr[i], var->key, len + 1);
	ft_strlcat(data(GET)->env_arr[i], "=", len + 1);
	ft_strlcat(data(GET)->env_arr[i], var->value, len + 1);
}

void	ct_env_set(void)
{
	int			i;
	t_env_var	*env;
	t_data		*ms_data;

	ms_data = data(GET);
	env = ms_data->env.first;
	i = ms_data->env.last->idx;
	ms_data->env_arr = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!ms_data->env_arr)
		minishell_exit(1, NULL);
	i = 0;
	while (env)
	{
		if (!env->value || env->was_unset)
		{
			env = env->next;
			continue ;
		}
		ct_env_set_var(env, i);
		i++;
		env = env->next;
	}
}
