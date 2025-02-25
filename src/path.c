/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:56 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 17:00:59 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/stdlib.h"
#include "minishell.h"

/**
 * If node is not present, then it was not present in env, so there is no
 * data(GET)->path
 */
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
