/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:59:06 by jwolfram          #+#    #+#             */
/*   Updated: 2025/01/07 16:51:26 by jwolfram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substrrplc(char *str, char *old, char *new)
{
	size_t	i;
	size_t	len;
	char	*res;

	len = ft_strlen(str) - ft_strlen(old) + ft_strlen(new);
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] != '$')
	{
		res[i] = str[i];
		i++;
	}
	ft_strlcat(res, new, len + 1);
	ft_strlcat(res, str + i, len + 1);
	return (res);
}

char	*ft_getenv(char *key)
{
	t_env_var	*var;
	
	var = data(GET)->env.first;
	while(var)
	{
		if (!ft_strcmp(key, var->key))
			return (var->value);
		var = var->next;
	}
	return (NULL);
}

static void	special_input_get(t_token *token, char type, size_t loc)
{
	size_t	len;
	char	*key;
	char	*tok_str;
	
	len = 1;
	tok_str = token->tok_str;
	if (type == '(')
	{
		while (tok_str[loc + len] != ')')	
			len++;
	//debug return
		return ;
	}
	else if (ft_isalpha(type))
	{
		while (ft_isalpha(tok_str[loc + len]) || tok_str[loc + len] == '_')
			len++;
		key = ft_substr(tok_str, loc, len);
		printf("key is %s\n", key);
		tok_str = ft_substrrplc(tok_str, key, ft_getenv(key + 1));
	}
	token->tok_str = tok_str;
}

void	special_input_replace(size_t i)
{
	t_token	*token;
	char	*tok_str;
	
	token = data(GET)->prompt[i]->first;
	while (token)
	{
		tok_str = token->tok_str;
		i = 0;
		while (tok_str[i])
		{
			if (tok_str[i] == '$' && tok_str[i + 1] 
				&& tok_str[i + 1] == '?')
			{
				tok_str = ft_substrrplc(tok_str, "$?", ft_itoa(data(GET)->exit_code));
				token->tok_str = tok_str;
				i++;
			}
			else if (tok_str[i] == '$' && tok_str[i + 1])
			{
				special_input_get(token, tok_str[i + 1], i);
				tok_str = token->tok_str;
				i++;
			}
			i++;
		}
		token = token->next;
	}
}
