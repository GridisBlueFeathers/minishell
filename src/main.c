/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:36:46 by svereten          #+#    #+#             */
/*   Updated: 2024/11/19 17:07:13 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc > 1)
		return (1);
	env_init(env);

	t_env_cont *content = data(GET)->env.first;
	while (content)
	{
		ft_printf("%s\n", content->key);
		ft_printf("%s\n", content->value);
		content = content->next;
	}
	return (0);
}
