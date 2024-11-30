/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:55 by svereten          #+#    #+#             */
/*   Updated: 2024/11/30 13:25:17 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

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
	int		exit_code;
	char	*rl_prompt;
	char	**path;
	t_env	env;
}	t_data;

t_data	*data(t_option option);
void	loop(void);
void	env_init(char **env);
void	env_free(t_env_var *node);
void	path_set(void);

void	lexer(void);

#endif
