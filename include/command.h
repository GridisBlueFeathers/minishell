/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:50:45 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 16:50:48 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "parser.h"

typedef struct s_redir
{
	struct s_redir	*first;
	t_tok_type		type;
	/* name of the redirect file, if type is HEREDOC - name of tmp file */
	char			*file_name;
	int				fd;
	char			*heredoc_delim;
	/* check if heredoc should expand env variables */
	int				heredoc_expand;
	struct s_redir	*next;
}	t_redir;

typedef enum e_cmd_type
{
	BIN,
	BUILTIN
}	t_cmd_type;

typedef struct s_cmd
{
	/* BIN or BUILTIN */
	t_cmd_type		type;
	/* command name with path to command file */
	char			*bin;
	/* command name */
	char			*name;
	/* array of command arguments */
	char			**argv;
	/* for check if last command */
	int				idx;
	int				from_path;
	pid_t			pid;
	/* to prevent execution of everything but heredocs */
	int				redir_valid;
	t_redir			*redir_head;
	t_redir			*redir_tail;
}	t_cmd;

typedef enum e_pipe
{
	RD,
	WR
}	t_pipe;

void	executor(void);

void	commands_reset(void);
int		commands_heredocs_run(void);

int		cmd_execute(t_cmd *cmd);
int		cmd_execute_single_bin(t_cmd *cmd);
void	cmd_execute_single_builtin(t_cmd *cmd);
int		cmd_heredoc_run(t_cmd *cmd);

void	heredoc_handle(t_redir *redir);

void	child(t_cmd *cmd, int pipe_fd[2]);
int		child_apply_redirs(t_cmd *cmd);
void	child_single(t_cmd *cmd);
void	child_execute(t_cmd *cmd);
void	child_kill(t_cmd *cmd);

#endif
