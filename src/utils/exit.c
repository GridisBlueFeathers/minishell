/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:15:33 by svereten          #+#    #+#             */
/*   Updated: 2025/02/26 16:51:38 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	minishell_exit(int status, char *msg)
{
	data(FREE);
	close(0);
	close(1);
	clear_history();
	if (status)
		ft_panic(status, msg);
	ft_exit(status);
}
