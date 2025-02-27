/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:56:44 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/27 14:08:56 by svereten         ###   ########.fr       */
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
