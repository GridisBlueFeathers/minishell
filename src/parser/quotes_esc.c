/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:43:03 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/31 14:44:17 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_esc(char *str, char *res, size_t *i, size_t *j)
{
	int	idx;

	idx = *i;
	if (str[idx] == '"')
	{
		res[0] = '"';
		return (1);
	}
	else if (str[idx] == '\'' && valid_operator(str, idx, 0))
	{
		res[0] = '\'';
		return (1);
	}
	res[0] = '\\';
	res[1] = '\'';
	*i += 1;
	*j += 1;
	return (0);
}
