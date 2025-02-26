/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:55:08 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 17:00:31 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_data	*data_init(void)
{
	t_data	*ptr;

	ptr = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!ptr)
		minishell_exit(1, NULL);
	return (ptr);
}

static void	data_free(t_data *ptr)
{
	if (!ptr)
		return ;
	if (ptr->rl_prompt)
		ft_free(STR, &ptr->rl_prompt);
	if (ptr->env.first)
		env_free(ptr->env.first);
	if (ptr->path)
		ft_free(STR_ARR, &ptr->path);
	ft_free(STRUCT, &ptr);
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
