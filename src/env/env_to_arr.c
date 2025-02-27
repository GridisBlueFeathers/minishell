/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:53:51 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:53:53 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_set_underscore(t_cmd *cmd, t_env_var *var)
{
	int	args_len;

	if (var->value)
		ft_free(STR, &var->value);
	args_len = ft_strarrlen(cmd->argv);
	if (args_len)
		var->value = ft_strdup(cmd->argv[args_len - 1]);
	else
		var->value = ft_strdup("");
	if (!var->value)
		minishell_exit(1, NULL);
}

static void	env_set_var(t_cmd *cmd, t_env_var *var, int i)
{
	size_t	len;
	t_data	*ms_data;

	if (ft_strcmp(var->key, "_") == 0)
		env_set_underscore(cmd, var);
	len = ft_strlen(var->key) + ft_strlen(var->value) + 1;
	ms_data = data(GET);
	ms_data->env_arr[i] = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ms_data->env_arr[i])
		minishell_exit(1, NULL);
	ft_strlcat(ms_data->env_arr[i], var->key, len + 1);
	ft_strlcat(ms_data->env_arr[i], "=", len + 1);
	ft_strlcat(ms_data->env_arr[i], var->value, len + 1);
}

static	int	env_get_len(void)
{
	int			res;
	t_env_var	*cur;

	res = 0;
	cur = data(GET)->env.first;
	while (cur)
	{
		if (cur->value && !cur->was_unset)
			res++;
		cur = cur->next;
	}
	return (res);
}

void	env_to_arr(t_cmd *cmd)
{
	int			i;
	t_env_var	*env;
	t_data		*ms_data;

	ms_data = data(GET);
	env = ms_data->env.first;
	i = env_get_len();
	if (ms_data->env_arr)
		ft_free(STR_ARR, &(data(GET)->env_arr));
	ms_data->env_arr = (char **)ft_calloc(i + 1, sizeof(char *));
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
		env_set_var(cmd, env, i);
		i++;
		env = env->next;
	}
	path_set();
}
