/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:26:32 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 17:10:28 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/string.h"
#include "libft/stdlib.h"

char	*ft_substr(char const *s, size_t start, size_t end)
{
	char			*res;
	unsigned int	new_len;
	unsigned int	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		new_len = 0;
	else if (end > ft_strlen(s) - start)
		new_len = ft_strlen(s) - start;
	else
		new_len = end;
	res = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (!res)
		return (0);
	i = start;
	while ((i < end + start) && s[i] && start < ft_strlen(s))
	{
		res[i - start] = s[i];
		i++;
	}
	return (res);
}
