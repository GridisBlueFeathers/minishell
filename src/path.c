/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:50:10 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/13 14:21:54 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/stdlib.h"
#include "minishell.h"

void	path_set(void)
{
	t_env_var	*node;	

	node = ft_getenv_node("PATH");
	if (!node)
		return ;
	if (data(GET)->path)
		ft_free(STR_ARR, &data(GET)->path);
	if (node->value)
		data(GET)->path = ft_split(node->value, ':');
}
