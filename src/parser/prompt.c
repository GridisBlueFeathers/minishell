/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:34:06 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/07 15:28:31 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/stdio.h"
#include "minishell.h"

void	prompt_init(void)
{
	t_data	*ms_data;
	char	**prompt;
	int		len;
	int		i;

	ms_data = data(GET);
	prompt = minishell_split(ms_data->rl_prompt);
	ft_putstrarr_fd(prompt, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	if (!prompt)
		minishell_exit(1, NULL);
	i = 0;
	len = ft_strarrlen(prompt);
	ms_data->prompt = (t_prompt **)ft_calloc(len + 1, sizeof(t_prompt *));
	if (!ms_data->prompt)
		minishell_exit(1, NULL);
	while (i < len)
	{
		ms_data->prompt[i] = (t_prompt *)ft_calloc(1, sizeof(t_prompt));
		if (!ms_data->prompt[i])
			minishell_exit(1, NULL);
		ms_data->prompt[i]->name = prompt[i];
		ms_data->prompt[i]->idx = i;
		i++;
	}
}

void	parser_init(void)
{
	size_t		i;

	i = 0;
	prompt_init();
	while (data(GET)->prompt[i])
	{
		printf("hello world\n");
		data(GET)->prompt[i]->idx = i;
		token_init(data(GET)->prompt[i]);
		special_input_replace(i);
		i++;
	}
}
