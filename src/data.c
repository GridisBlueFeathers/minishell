/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:55:08 by jwolfram          #+#    #+#             */
/*   Updated: 2024/11/21 17:35:47 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static t_data	*data_init(void)
{
	t_data	*ptr;

	ptr = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!ptr)
		ft_panic(1, NULL);
	ptr->env.first = NULL;
	ptr->env.last = NULL;
	ptr->path = NULL;
	return (ptr);
}

static void	data_free(t_data *ptr)
{
	if (ptr->env.first)
		env_free(ptr->env.first);
	if (ptr->path)
		ft_free(STR_ARR, &ptr->path);
	free(ptr);
}

t_data	*data(t_option option)
{
	static t_data	*ptr;

	if (option == GET)
	{
		if (!ptr)
			ptr = data_init();
	}
	if (option == FREE)
	{
		data_free(ptr);
		ptr = NULL;
	}
	return (ptr);
}
