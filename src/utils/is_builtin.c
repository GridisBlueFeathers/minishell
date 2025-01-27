/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 14:23:58 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/24 15:15:22 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *name)
{
	if (!ft_strncmp(name, "echo", ft_strlen(name))
		|| !ft_strncmp(name, "cd", ft_strlen(name))
		|| !ft_strncmp(name, "pwd", ft_strlen(name))
		|| !ft_strncmp(name, "exit", ft_strlen(name))
		|| !ft_strncmp(name, "env", ft_strlen(name))
		|| !ft_strncmp(name, "export", ft_strlen(name))
		|| !ft_strncmp(name, "unset", ft_strlen(name)))
		return (1);
	return (0);
}
