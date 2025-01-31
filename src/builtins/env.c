/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:14:40 by svereten          #+#    #+#             */
/*   Updated: 2025/01/31 13:41:47 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"
#include "minishell.h"
#include "command.h"

/**
 * For each node len + 2 for '=' and '\n'
 */
static size_t	env_get_len(void)
{
	t_env_var	*cur;
	size_t		len;

	len = 0;
	cur = data(GET)->env.first;
	while (cur)
	{
		if (cur->was_unset)
		{
			cur = cur->next;
			continue ;
		}
		len += ft_strlen(cur->key) + 2;
		if (cur->value)
			len += ft_strlen(cur->value);
		cur = cur->next;
	}
	return (len);
}

static char	*env_get_output(void)
{
	t_env_var	*cur;
	char		*output;
	size_t		len;

	len = env_get_len();
	output = (char *)ft_calloc(len + 1, sizeof(char));
	if (!output)
		minishell_exit(1, NULL);
	cur = data(GET)->env.first;
	while (cur)
	{
		if (cur->was_unset)
		{
			cur = cur->next;
			continue ;
		}
		ft_strlcat(output, cur->key, len + 1);
		ft_strlcat(output, "=", len + 1);
		ft_strlcat(output, cur->value, len + 1);
		ft_strlcat(output, "\n", len + 1);
		cur = cur->next;
	}
	return (output);
}

/**
 * Why allocating a separate string for output while `printf` is availible?
 * `printf` might fail at each iteration, which is a pain in the ass to track
 * separate string might fail only twice: at allocation and at writing
 */
int	builtin_env(t_cmd *cmd)
{
	char		*output;

	if (ft_strarrlen(cmd->argv) > 1)
	{
		ft_putstr_fd("minishell: env: too many agruments\n", STDERR_FILENO);
		return (1);
	}
	output = env_get_output();
	if (ft_putstr_fd(output, STDOUT_FILENO) < 0)
		minishell_exit(1, NULL);
	return (0);
}
