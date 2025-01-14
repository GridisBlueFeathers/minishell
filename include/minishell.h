/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:55 by svereten          #+#    #+#             */
/*   Updated: 2025/01/14 17:06:27 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "command.h"

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

typedef enum e_mode
{
	IN_PROMPT,
	IN_HEREDOC,
}	t_mode;

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
	t_env		env;
	t_cmd		**commands;
	char		**path;
	char		*rl_prompt;
	int			stdin_copy;
	int			stdout_copy;
	int			exit_code;
	int			cmd_amount;
	t_mode		mode;
	t_prompt	**prompt;
}	t_data;

/* dev functions */
/* ------------- */

void	debug_print(void);
void	env_print(void);
void	tokenizer_print(void);

/* ------------- */

t_data	*data(t_option option);
void	loop(void);

void	env_init(char **env);
void	env_free(t_env_var *node);
void	path_set(void);
void	env_update(void);

int		isredir(char c);
void	redirect(int old_fd, int new_fd);
void	pipe_close(int pipe_fd[2]);
void	stdfd_copy(void);
void	stdfd_reset(void);
void	stdfd_close(void);
int		isquote(char c);
size_t	wordlen(char *str);
char	*ft_getenv(char *key);
int		valid_operator(char *str, size_t loc, char type);

char	**minishell_split(char *str);

int		lexer(void);

void	signal_init(void);
void	signal_int(int signal);

void	minishell_exit(int status, char *msg);

#endif
