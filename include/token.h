/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:01:49 by jwolfram          #+#    #+#             */
/*   Updated: 2024/12/02 19:05:02 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_tok_type
{
	WORD,
	APPEND,
	HEREDOC,
	INPUT,
	OUTPUT,
	PIPE
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
	t_token	*first;
	t_token	*last;
}	t_prompt;

void	prompt_init(void);

#endif
