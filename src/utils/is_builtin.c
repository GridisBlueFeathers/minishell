/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:57:08 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:57:09 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *name)
{
	if (!ft_strcmp(name, "echo")
		|| !ft_strcmp(name, "cd")
		|| !ft_strcmp(name, "pwd")
		|| !ft_strcmp(name, "exit")
		|| !ft_strcmp(name, "env")
		|| !ft_strcmp(name, "export")
		|| !ft_strcmp(name, "unset"))
		return (1);
	return (0);
}
