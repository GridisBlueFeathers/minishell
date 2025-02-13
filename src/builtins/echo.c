/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:39:13 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/13 14:19:37 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	check;

	i = 1;
	if (cmd->argv[1] && !ft_strcmp("-n", cmd->argv[1]))
		i = 2;
	while (cmd->argv[i])
	{
		if (!cmd->argv[i + 1])
			check = printf("%s", cmd->argv[i]);
		else if (ft_strcmp("-n", cmd->argv[i]))
			check = printf("%s ", cmd->argv[i]);
		if (check < 0)
			return (1);
		i++;
	}
	if (!cmd->argv[1] || ft_strcmp("-n", cmd->argv[1]))
		check = printf("\n");
	if (check < 0)
		return (1);
	return (0);
}
