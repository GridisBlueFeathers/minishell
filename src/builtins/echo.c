/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:39:13 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:05:34 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_minus_n(char *str)
{
	int	i;

	i = 1;
	if (ft_strcmp(str, "-") == 0)
		return (0);
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	get_output_len(t_cmd *cmd)
{
	size_t	res;
	int		i;

	i = 1;
	res = 0;
	while (cmd->argv[i] && is_minus_n(cmd->argv[i]))
		i++;
	while (cmd->argv[i])
	{
		res += ft_strlen(cmd->argv[i]);
		if (cmd->argv[i + 1])
			res++;
		i++;
	}
	if (!cmd->argv[1] || (cmd->argv[1] && !is_minus_n(cmd->argv[1])))
		res++;
	return (res);
}

static char	*create_output(t_cmd *cmd)
{
	char	*res;
	int		i;
	size_t	len;

	len = get_output_len(cmd);
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		minishell_exit(1, NULL);
	i = 1;
	while (cmd->argv[i] && is_minus_n(cmd->argv[i]))
		i++;
	while (cmd->argv[i])
	{
		ft_strlcat(res, cmd->argv[i], len + 1);
		if (cmd->argv[i + 1])
			ft_strlcat(res, " ", len + 1);
		i++;
	}
	if (!cmd->argv[1] || (cmd->argv[1] && !is_minus_n(cmd->argv[1])))
		ft_strlcat(res, "\n", len + 1);
	return (res);
}

int	builtin_echo(t_cmd *cmd)
{
	char	*res;

	res = create_output(cmd);
	if (ft_putstr_fd(res, STDOUT_FILENO) < 0)
	{
		ft_free(STR, &res);
		minishell_exit(1, NULL);
	}
	return (ft_free(STR, &res), 0);
}
