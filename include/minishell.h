/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:55 by svereten          #+#    #+#             */
/*   Updated: 2024/11/19 17:07:59 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "libft/ft_printf.h"

typedef enum e_option
{
	GET,
	FREE
}	t_option;

typedef struct s_env_cont
{
	char				*key;
	char				*value;
	struct s_env_cont	*next;
	struct s_env_cont	*prev;
}	t_env_cont;

typedef struct s_env
{
	t_env_cont	*first;
	t_env_cont	*last;
}	t_env;

typedef struct s_data
{
	int		nbr;
	t_env	env;
}	t_data;

t_data	*data(t_option option);
void	env_init(char **env);
void	print_env(char **env);

#endif
