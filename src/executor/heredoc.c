/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:55:15 by svereten          #+#    #+#             */
/*   Updated: 2025/01/14 17:39:55 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include "minishell.h"

static char	*heredoc_get_name(void)
{
	int		urandom_fd;
	int		i;
	int		c;
	char	*res;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd == -1)
		minishell_exit(1, NULL);
	res = (char *)ft_calloc(22, sizeof(char));
	if (!res)
		return (ft_close(urandom_fd), NULL);
	ft_strlcpy(res, "/tmp/", 22);
	i = 0;
	c = 0;
	while (i < 16)
	{
		if (read(urandom_fd, &c, 1) < 0)
			return (ft_close(urandom_fd), NULL);
		if (!isalpha(c % 256))
			continue ;
		res[i + 5] = (unsigned char)c % 256;
		i++;
	}
	return (ft_close(urandom_fd), res);
}

void	heredoc_handle(t_redir *redir)
{
	char	*heredoc_line;

	redir->file_name = heredoc_get_name();
	if (!redir->file_name)
		minishell_exit(1, NULL);
	dprintf(STDERR_FILENO, "Heredoc file name is %s\n", redir->file_name);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
		minishell_exit(1, NULL);
	while (data(GET)->mode == IN_HEREDOC)
	{
		heredoc_line = readline("> ");
		if (!heredoc_line)
			ft_putstr_fd("warning: heredoc delimited by EOF\n", STDERR_FILENO);
		if (!heredoc_line || !ft_strcmp(heredoc_line, redir->heredoc_delim))
			break ;
		if (ft_putendl_fd(heredoc_line, redir->fd) < 0)
		{
			(ft_free(STR, &heredoc_line), ft_close(redir->fd));
			minishell_exit(1, NULL);
		}
		ft_free(STR, &heredoc_line);
	}
	ft_free(STR, &heredoc_line);
	ft_close(redir->fd);
	return ;
}
