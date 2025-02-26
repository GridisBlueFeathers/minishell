/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_has_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:58:43 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:58:44 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_has_quotes(char *str)
{
	if (ft_strchr(str, '\'') || ft_strchr(str, '"'))
		return (1);
	return (0);
}
