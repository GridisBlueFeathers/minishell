/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:50:10 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/21 17:37:35 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	path_set(void)
{
	t_env_var	*node;	

	node = data(GET)->env.first;
	while (ft_strcmp(node->key, "PATH"))
		node = node->next;
	data(GET)->path = ft_split(node->value, ':');
	if (!data(GET)->path)
		ft_panic(1, NULL);
}
