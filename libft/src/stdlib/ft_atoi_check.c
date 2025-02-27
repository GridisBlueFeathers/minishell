/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:03 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 17:21:40 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/stdlib.h"
#include "libft/string.h"

int	ft_atoi_check(char *str, int *res)
{
	char	*itoa_res;

	*res = ft_atoi(str);
	itoa_res = ft_itoa(*res);
	if (!itoa_res || ft_strcmp(str, itoa_res))
		return (ft_free(STR, &itoa_res), 0);
	return (ft_free(STR, &itoa_res), 1);
}
