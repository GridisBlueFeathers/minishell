/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:14:40 by svereten          #+#    #+#             */
/*   Updated: 2025/01/31 13:30:08 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"
#include "minishell.h"
#include "command.h"

/**
 * For each node len + 2 for '=' and '\n'
 * Why allocating a separate string for output while `printf` is availible?
 * `printf` might fail at each iteration, which is a pain in the ass to track
 * separate string might fail only twice: at allocation and at writing
 */
int	builtin_env(t_cmd *cmd)
{
	size_t		len;
	t_env_var	*cur;
	char		*output;

	if (ft_strarrlen(cmd->argv) > 1)
	{
		ft_putstr_fd("minishell: env: too many agruments\n", STDERR_FILENO);
		return (1);
	}
	len = 0;
	cur = data(GET)->env.first;
	while (cur)
	{
		if (cur->was_unset)
		{
			cur = cur->next;
			continue ;
		}
		len += ft_strlen(cur->key) + ft_strlen(cur->value) + 2;
		cur = cur->next;
	}
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
	if (ft_putstr_fd(output, STDIN_FILENO) < 0)
		minishell_exit(1, NULL);
	return (0);
}
