/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substri.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:13:00 by svereten          #+#    #+#             */
/*   Updated: 2025/01/11 16:38:27 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"
#include "libft/stdlib.h"

char	*ft_substri(char *str, size_t start, size_t finish)
{
	char	*res;
	size_t	i;

	if (!str)
		return (NULL);
	if (finish < start || start > ft_strlen(str))
		return (ft_calloc(1, sizeof(char)));
	res = (char *)ft_calloc(finish - start + 2, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (str[start + i] && start + i <= finish)
	{
		res[i] = str[start + i];
		i++;
	}
	return (res);
}
