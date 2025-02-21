/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_first_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:42:27 by svereten          #+#    #+#             */
/*   Updated: 2025/02/21 15:03:43 by svereten         ###   ########.fr       */
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
