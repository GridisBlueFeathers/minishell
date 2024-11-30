/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:55 by svereten          #+#    #+#             */
/*   Updated: 2024/11/30 14:24:58 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/stdio.h"
# include "libft/stdlib.h"
# include "libft/string.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PREFIX_GOOD "\ueab2 minishell \uf061  "
# define PREFIX_BAD "\uea76 minishell \uf061  "

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
	char	*rl_prefix;
	char	**path;
	t_env	env;
}	t_data;

t_data	*data(t_option option);
void	loop(void);
void	env_init(char **env);
void	env_free(t_env_var *node);
void	path_set(void);

void	signal_init(void);
void	signal_int(int signal);

void	minishell_exit(int status, char *msg);

#endif
