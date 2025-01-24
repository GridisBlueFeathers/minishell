/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:09:01 by svereten          #+#    #+#             */
/*   Updated: 2025/01/24 13:58:47 by jwolfram         ###   ########.fr       */
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
	t_redir			*redir_head;
	t_redir			*redir_tail;
	struct s_cmd	*next;
}	t_cmd;

#endif
