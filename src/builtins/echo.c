/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:39:13 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/31 16:10:16 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	check;

	i = 1;
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == 'n')
		i = 2;
	while (cmd->argv[i + 1])
	{
		check = printf("%s ", cmd->argv[i]);
		if (check < 0)
			return (1);
		i++;
	}
	if (cmd->argv[1][0] == '-' && cmd->argv[1][1] == 'n')
		check = printf("%s", cmd->argv[i]);
	else
		check = printf("%s\n", cmd->argv[i]);
	if (check < 0)
		return (1);
	return (0);
}
