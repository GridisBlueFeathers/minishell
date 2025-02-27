/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:47 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 17:03:54 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"
#include "minishell.h"

static char	*exp_new_str_init(char *old, int in_heredoc)
{
	char	*new;

	if (!old)
		return (NULL);
	if (!ft_strcmp(old, "$?"))
	{
		new = ft_itoa(data(GET)->exit_code);
		if (!new)
			minishell_exit(1, NULL);
	}
	else
	{
		new = ft_getenv(old + 1);
		if (new)
			new = ft_strdup(new);
		if (in_heredoc && (!new || !ft_strlen(new)))
			new = ft_strdup("");
		else if ((!new || !ft_strlen(new)))
			new = ft_strdup("\"\"");
		if (!new)
			minishell_exit(1, NULL);
	}
	return (new);
}

static char	*exp_find_str(char *str)
{
	char	*res;
	size_t	len;

	len = 1;
	while (str[len] && (str[len] == '_' || ft_isalnum(str[len])))
		len++;
	res = ft_substr(str, 0, len);
	if (!res)
		minishell_exit(1, NULL);
	return (res);
}

static char	*exp_old_str_init(char *str, size_t loc)
{
	size_t	i;
	char	quote;
	char	*res;

	i = 0;
	quote = 0;
	res = NULL;
	while (str[i])
	{
		if (!quote && isquote(str[i]))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		if (str[loc] == str[i] && quote != '\'' && !heredoc_var(str, loc))
		{
			if (str[i + 1] == '?')
				res = ft_strdup("$?");
			else if (ft_isalpha(str[i + 1]) || str[i + 1] == '_')
				res = exp_find_str(str + i);
			break ;
		}
		i++;
	}
	return (res);
}

char	*expander_str(char *str)
{
	size_t	i;
	char	*old_str;
	char	*new_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			old_str = exp_old_str_init(str, i);
			if (!old_str)
				break ;
			new_str = exp_new_str_init(old_str, 1);
			str = substrrplc(str, old_str, new_str);
			if (!str[i])
				break ;
		}
		i++;
	}
	return (str);
}

void	expander_init(t_prompt *prompt)
{
	size_t	i;
	char	*old_str;
	char	*new_str;

	i = 0;
	while (prompt->name[i])
	{
		if (prompt->name[i] == '$' && prompt->name[i + 1])
		{
			old_str = exp_old_str_init(prompt->name, i);
			if (!old_str)
				break ;
			if (is_first_word(prompt->name, old_str))
				new_str = exp_new_str_init(old_str, 1);
			else
				new_str = exp_new_str_init(old_str, 0);
			prompt->name = substrrplc(prompt->name, old_str, new_str);
			if (!prompt->name[i])
				break ;
		}
		i++;
	}
}
