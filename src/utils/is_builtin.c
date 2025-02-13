/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:23:58 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/13 13:51:22 by svereten         ###   ########.fr       */
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
