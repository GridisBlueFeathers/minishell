/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:00:51 by svereten          #+#    #+#             */
/*   Updated: 2025/02/10 15:43:55 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "command.h"
#include "libft/string.h"
#include "minishell.h"
#include <stdio.h>
#include <dirent.h>
#include <errno.h>

/**
 * If PWD value doesn't exist, OLDPWD will be set to NULL
 */
static void	cd_handle_oldpwd(void)
{
	t_env_var	*oldpwd;
	t_env_var	*pwd;

	oldpwd = ft_get_alloc_env_node("OLDPWD");
	if (oldpwd->value)
		ft_free(STR, &oldpwd->value);
	pwd = ft_get_alloc_env_node("PWD");
	oldpwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
		minishell_exit(1, NULL);
}

static int	cd_directory_check(char *target)
{
	if (is_directory(target))
		return (1);
	else if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		return (perror(target), 0);
	}
	else
		minishell_exit(1, NULL);
	return (0);
}

static char	*cd_get_home(void)
{
	t_env_var	*home;

	home = ft_getenv_node("HOME");
	if (!home || home->was_unset)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (home->value);
}

int	builtin_cd(t_cmd *cmd)
{
	char		*target;
	int			err;

	if (ft_strarrlen(cmd->argv) > 2)
	{
		ft_putstr_fd("minishell: cd: too many agruments\n", STDERR_FILENO);
		return (1);
	}
	if (!cmd->argv[1])
	{
		target = cd_get_home();
		if (!target)
			return (1);
	}
	else
		target = cmd->argv[1];
	if (!cd_directory_check(target))
		return (1);
	err = chdir(target);
	if (err < 0)
		minishell_exit(1, NULL);
	cd_handle_oldpwd();
	return (0);
}
