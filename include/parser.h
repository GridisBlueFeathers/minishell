/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:01:49 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/25 14:31:43 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

typedef enum e_tok_type
{
	EOP,
	WORD,
	APPEND,
	HEREDOC,
	INPUT,
	OUTPUT,
	HRDC_EXPND,
	CMD
}	t_tok_type;

typedef struct s_token
{
	t_tok_type		tok_type;
	char			*tok_str;	
	size_t			idx;
	struct s_token	*next;
}	t_token;

typedef struct s_prompt
{
	char	*name;
	size_t	idx;
	t_token	*first;
	t_token	*last;
}	t_prompt;

void	parser(void);
void	prompt_init(void);
void	expander_init(t_prompt *prompt);
void	token_init(t_prompt *prompt);
char	*expander_str(char *str);

void	quotes_rm_init(t_token *token);
int		quote_is_valid(char *str, size_t loc, char type);

void	command_table_init(void);
void	redir_set(t_token *token, int idx);
void	ct_argv_set(t_prompt *prompt);
void	ct_env_set(void);

size_t	wordcount(char *str);
char	*substrrplc(char *main_str, char *old_str, char *new_str);

#endif
