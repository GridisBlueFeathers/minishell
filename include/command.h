/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:09:01 by svereten          #+#    #+#             */
/*   Updated: 2025/01/27 14:41:25 by jwolfram         ###   ########.fr       */
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
int		cmd_heredoc_run(t_cmd *cmd);

void	heredoc_handle(t_redir *redir);

void	child(t_cmd *cmd, int pipe_fd[2]);
void	child_single(t_cmd *cmd);
void	child_execute(t_cmd *cmd);
void	child_kill(t_cmd *cmd);

/**
 * DEV function - delete on production
 *
 * mocks `cat Makefile` command
 */
void	dev_shim_prompt(void);
void	dev_mock_cat_make(void);
void	dev_mock_echo_hi(void);
void	dev_mock_cat_dev2(void);
void	dev_mock_cat_pipe_grep(void);
void	dev_mock_cat_pipe_grep_pipe_wc(void);
void	dev_mock_cat_heredoc(void);

#endif
