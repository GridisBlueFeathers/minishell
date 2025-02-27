/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:51:04 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 17:55:15 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "command.h"

# define PREFIX_GOOD "\ueab2 minishell \uf061  "
# define PREFIX_BAD "\uea76 minishell \uf061  "

# define NL_ERROR "minishell: syntax error near unexpected token `newline'\n"

typedef enum e_option
{
	GET,
	FREE
}	t_option;

typedef enum e_mode
{
	IN_PROMPT,
	IN_EXECUTION,
	IN_HEREDOC,
}	t_mode;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	int					idx;
	struct s_env_var	*next;
	struct s_env_var	*prev;
	int					was_unset;
}	t_env_var;

typedef struct s_env
{
	t_env_var	*first;
	t_env_var	*last;
	char		**arr;
}	t_env;

typedef struct s_data
{
	t_env		env;
	t_cmd		**commands;
	char		**path;
	char		*rl_prompt;
	char		**env_arr;
	int			stdin_copy;
	int			stdout_copy;
	int			exit_code;
	int			cmd_amount;
	int			line_num;
	t_mode		mode;
	t_prompt	**prompt;
}	t_data;

t_data		*data(t_option option);
void		loop(void);

t_env_var	*env_allocate(void);
void		env_init(char **env);
void		env_free(t_env_var *node);
void		env_to_arr(t_cmd *cmd);
void		path_set(void);

int			isredir(char c);
/**
 * Old fd MUST be passed by reference
*/
void		redirect(int *old_fd, int new_fd);
void		pipe_close(int pipe_fd[2]);
void		stdfd_copy(void);
void		stdfd_restore(void);
void		stdfd_close(void);
int			isquote(char c);
int			is_builtin(char *name);
int			is_directory(char *path);
int			is_first_word(char *big, char *small);
size_t		wordlen(char *str);
char		*ft_getenv(char *key);
t_env_var	*ft_getenv_node(char *key);
t_env_var	*ft_get_alloc_env_node(char *key);
int			str_has_quotes(char *str);
int			str_isspace(char *str);
int			valid_operator(char *str, size_t loc, char type);
int			heredoc_var(char *str, size_t loc);

char		**minishell_split(char *str);

int			lexer(void);
int			lexer_redir_check(void);
void		lexer_error(char error, char redir);

void		signal_init(void);
void		signal_int(int signal);
void		signal_pipe(int signal);

int			builtin_cd(t_cmd *cmd);
int			builtin_env(t_cmd *cmd);
int			builtin_export(t_cmd *cmd);
int			builtin_export_no_args(void);
int			builtin_unset(t_cmd *cmd);
int			builtin_echo(t_cmd *cmd);
int			builtin_pwd(void);
int			builtin_exit(t_cmd *cmd);

void		minishell_exit(int status, char *msg);

#endif
