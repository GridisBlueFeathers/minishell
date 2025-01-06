/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:45:30 by svereten          #+#    #+#             */
/*   Updated: 2025/01/06 18:12:59 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	cmd_free(t_cmd *cmd)
{
	t_redir	*cur;
	t_redir	*tmp;

	ft_free(STR, &cmd->bin);
	ft_free(STR, &cmd->name);
	ft_free(STR_ARR, &cmd->argv);
	cur = cmd->redir_head;
	while (cur)
	{
		tmp = cur->next;
		if (cur->type == HEREDOC)
			unlink(cur->file_name);
		ft_free(STR, &cur->file_name);
		cur = tmp;
	}
	ft_free(STRUCT, &cmd);
	return ;
}

void	commands_reset(void)
{
	int	i;

	i = 0;
	while (data(GET)->commands[i])
	{
		cmd_free(data(GET)->commands[i]);
		i++;
	}
	ft_free(STRUCT, &data(GET)->commands);
	data(GET)->cmd_amount = 0;
}
