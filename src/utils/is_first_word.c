/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_first_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:57:27 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:57:29 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_first_word(char *big, char *small)
{
	size_t	i;

	i = 0;
	while (isspace(big[i]))
		i++;
	if (!ft_strncmp(small, big + i, ft_strlen(small)))
		return (1);
	return (0);
}
