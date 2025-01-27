/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 14:47:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/27 15:12:39 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ms_data->env_arr[i] = ft_strdup(env->key);
		if (!ms_data->env_arr[i])
			minishell_exit(1, NULL);
		ms_data->env_arr[i] = ft_strjoin(ms_data->env_arr[i], "=");
		if (!ms_data->env_arr[i])
			minishell_exit(1, NULL);
		ms_data->env_arr[i] = ft_strjoin(ms_data->env_arr[i], env->value);
		if (!ms_data->env_arr[i])
			minishell_exit(1, NULL);
		i++;
		env = env->next;
	}
}
