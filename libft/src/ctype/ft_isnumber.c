/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:38:07 by svereten          #+#    #+#             */
/*   Updated: 2025/02/21 19:03:38 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/ctype.h"
#include "libft/string.h"
#include <stdio.h>
#include <unistd.h>

static int	find_beginning(char *str)
{
	int	res;

	res = 0;
	while (str[res] && ft_isspace(str[res]))
		res++;
	if (str[res] == '-' || str[res] == '+')
		res++;
	while (str[res] && str[res] == '0')
		res++;
	return (res);
}

static int	basic_check(char *str)
{
	int	i;
	int	has_digits;

	i = 0;
	has_digits = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		has_digits = 1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (has_digits);
}

static int	number_len(char *str)
{
	int	res;

	res = 0;
	while (str[res] && ft_isdigit(str[res]))
		res++;
	return (res);
}

/**
 * For way too big of numbers check is performed in basic check
 * For overflow check if strlen is less than 20, it won't overflow int64
 */
int	ft_isnumber(char *str)
{
	int	i;

	if (!str || !basic_check(str))
		return (0);
	i = find_beginning(str);
	if (number_len(&str[i]) < 19)
		return (1);
	if (number_len(&str[i]) > 19)
		return (0);
	if (ft_strchr(str, '-')
		&& ft_strncmp(&str[i], LLONG_MIN_STR, ft_strlen(LLONG_MIN_STR)) <= 0)
		return (1);
	if (ft_strchr(str, '+')
		&& ft_strncmp(&str[i], LLONG_MAX_STR, ft_strlen(LLONG_MAX_STR)) <= 0)
		return (1);
	if ((!ft_strchr(str, '-') || !ft_strchr(str, '+'))
		&& ft_strncmp(&str[i], LLONG_MAX_STR, ft_strlen(LLONG_MAX_STR)) <= 0)
		return (1);
	return (0);
}
