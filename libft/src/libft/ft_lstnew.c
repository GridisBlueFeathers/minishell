/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:48:53 by svereten          #+#    #+#             */
/*   Updated: 2024/11/22 17:33:29 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/stdlib.h"
#include "libft/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*res;

	res = (t_list *)ft_calloc(1, sizeof(t_list));
	if (!res)
		return (0);
	res->content = content;
	res->next = 0;
	return (res);
}
