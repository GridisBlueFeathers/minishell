/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:01:49 by jwolfram          #+#    #+#             */
/*   Updated: 2024/12/06 16:24:26 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

typedef enum e_tok_type
{
	EOP,
	WORD,
	APPEND,
	HEREDOC,
	INPUT,
	OUTPUT
}	t_tok_type;

typedef struct s_token
{
	t_tok_type		tok_type;
	char			*tok_str;	
	struct s_token	*next;
}	t_token;

typedef struct s_prompt
{
	char	*name;
	size_t	idx;
	t_token	*first;
	t_token	*last;
}	t_prompt;

void	parser_init(void);

#endif
