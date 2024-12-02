/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:55 by svereten          #+#    #+#             */
/*   Updated: 2024/12/02 19:05:04 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "token.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PREFIX_GOOD "\ueab2 minishell \uf061  "
# define PREFIX_BAD "\uea76 minishell \uf061  "

# define ERR_QUOTES "minishell: syntax error near unexpected quotation marks\n"
# define ERR_PIPES "minishell: syntax error near unexpected pipe\n"
# define ERR_REDIRS "minishell: syntax error near unexpected redirection\n"

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
	int			exit_code;
	char		*rl_prompt;
	char		*rl_prefix;
	char		**path;
	t_prompt	**prompt;
	t_env		env;
}	t_data;

t_data	*data(t_option option);
void	loop(void);

void	env_init(char **env);
void	env_free(t_env_var *node);
void	path_set(void);

int		isredir(char c);
size_t	wordlen(char *str);

int		lexer(void);

void	signal_init(void);
void	signal_int(int signal);

void	minishell_exit(int status, char *msg);

#endif
