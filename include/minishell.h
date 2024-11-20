/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:55 by svereten          #+#    #+#             */
/*   Updated: 2024/11/20 17:32:52 by jwolfram         ###   ########.fr       */
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

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
	struct s_env_var	*prev;
}	t_env_var;

typedef struct s_env
{
	t_env_var	*first;
	t_env_var	*last;
}	t_env;

typedef struct s_data
{
	char	**path;
	t_env	env;
}	t_data;

t_data	*data(t_option option);
void	env_init(char **env);
void	free_env(t_env_var *node);
void	print_env(char **env);
void	set_path(void);

#endif
