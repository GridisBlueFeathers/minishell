/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:39:13 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/20 15:42:12 by svereten         ###   ########.fr       */
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

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	check;

	i = 1;
	while (cmd->argv[i] && is_minus_n(cmd->argv[i]))
		i++;
	while (cmd->argv[i])
	{
		if (!cmd->argv[i + 1])
			check = printf("%s", cmd->argv[i]);
		else
			check = printf("%s ", cmd->argv[i]);
		if (check < 0)
			return (1);
		i++;
	}
	if (!cmd->argv[1] || (cmd->argv[1] && !is_minus_n(cmd->argv[1])))
		check = printf("\n");
	if (check < 0)
		return (1);
	return (0);
}
