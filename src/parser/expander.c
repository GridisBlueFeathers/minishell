/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:59:06 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/10 16:17:26 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/string.h"
#include "minishell.h"

static char	*exp_new_str_init(char	*old)
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
	}
	return (new);
}

static char	*exp_find_str(char *str)
{
	char	*res;
	size_t	len;

	len = 1;
	while (str[len] && (str[len] == '_' || ft_isalpha(str[len])))
		len++;
	res = ft_substr(str, 0, len);
	if (!res)
		minishell_exit(1, NULL);
	return (res);
}

static char	*exp_old_str_init(char *str)
{
	size_t	i;
	char	*res;

	i = 0;
	res = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && valid_operator(str, i, '\''))
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
	char	*old_str;
	char	*new_str;

	while (ft_strchr(str, '$'))
	{
		old_str = exp_old_str_init(str);
		if (!old_str)
			break ;
		new_str = exp_new_str_init(old_str);
		str = substrrplc(str, old_str, new_str);
	}
	return (str);
}

void	expander_init(t_prompt *prompt)
{
	size_t	i;
	char	*old_str;
	char	*new_str;

	i = 0;
	while (ft_strchr(prompt->name, '$'))
	{
		old_str = exp_old_str_init(prompt->name);
		if (!old_str)
			break ;
		new_str = exp_new_str_init(old_str);	
		prompt->name = substrrplc(prompt->name, old_str, new_str);
		i++;
	}
}
