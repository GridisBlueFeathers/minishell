/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:09:01 by svereten          #+#    #+#             */
/*   Updated: 2025/01/06 15:03:36 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef COMMAND_H
# define COMMAND_H

#include <sys/types.h>
typedef enum e_redir_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
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
	int				index;
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

/**
 * DEV function - delete on production
 *
 * mocks `cat Makefile` command
 */
void	dev_mock_cat_make(void);
void	dev_mock_echo_hi(void);
void	dev_mock_cat_dev2(void);
void	dev_mock_cat_pipe_grep(void);
void	dev_mock_cat_pipe_grep_pipe_wc(void);

#endif
