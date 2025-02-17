/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:31:44 by svereten          #+#    #+#             */
/*   Updated: 2025/02/17 13:30:08 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

/**
 * "export " strlen is 7 + '\n' makes 8
 * 3 additional characters for =""
 */
static size_t	export_get_len(void)
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
		len += ft_strlen(cur->key) + 8;
		if (cur->value)
			len += ft_strlen(cur->value) + 3;
		cur = cur->next;
	}
	return (len);
}

static void	export_concat_output(t_env_var *cur, char *output, size_t len)
{
	ft_strlcat(output, "export ", len + 1);
	ft_strlcat(output, cur->key, len + 1);
	if (cur->value)
	{
		ft_strlcat(output, "=\"", len + 1);
		ft_strlcat(output, cur->value, len + 1);
		ft_strlcat(output, "\"", len + 1);
	}
	ft_strlcat(output, "\n", len + 1);
}

static char	*export_get_output(void)
{
	t_env_var	*cur;
	char		*output;
	size_t		len;

	len = export_get_len();
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
		export_concat_output(cur, output, len);
		cur = cur->next;
	}
	return (output);
}

/**
 * Why not `printf`?
 * Same logic as env builtin
 */
int	builtin_export_no_args(void)
{
	char	*output;

	output = export_get_output();
	if (ft_putstr_fd(output, STDOUT_FILENO) < 0)
		minishell_exit(1, NULL);
	return (0);
}
