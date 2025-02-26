/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwolfram <jwolfram@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:55:07 by jwolfram          #+#    #+#             */
/*   Updated: 2025/02/26 17:03:24 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/stdlib.h"
#include "libft/string.h"
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
			return (ft_close(urandom_fd), ft_free(STR, &res), NULL);
		if (!isalpha(c % 256))
			continue ;
		res[i + 5] = (unsigned char)c % 256;
		i++;
	}
	return (ft_close(urandom_fd), res);
}

/**
 * "warning: here-document at line 2 delimited by end-of-file (wanted `"
 * strlen is 67
 */
static void	heredoc_eof_message(t_redir *redir)
{
	size_t	len;
	char	*res;
	char	*line_num_str;

	line_num_str = ft_itoa(data(GET)->line_num);
	if (!line_num_str)
		minishell_exit(1, NULL);
	len = 66 + ft_strlen(redir->heredoc_delim) + ft_strlen(line_num_str) + 3;
	res = (char *)ft_calloc(len + 1, sizeof(char));
	if (!res)
		(ft_free(STR, &line_num_str), minishell_exit(1, NULL));
	ft_strlcat(res, "warning: here-document at line ", len + 1);
	ft_strlcat(res, line_num_str, len + 1);
	ft_strlcat(res, " delimited by end-of-file (wanted `", len + 1);
	ft_strlcat(res, redir->heredoc_delim, len + 1);
	ft_strlcat(res, "')\n", len + 1);
	ft_putstr_fd(res, STDERR_FILENO);
	ft_free(STR, &line_num_str);
	ft_free(STR, &res);
}

static void	heredoc_feed(t_redir *redir)
{
	char	*heredoc_line;

	while (data(GET)->mode == IN_HEREDOC)
	{
		heredoc_line = readline("> ");
		if (!heredoc_line)
			heredoc_eof_message(redir);
		if (!heredoc_line || !ft_strcmp(heredoc_line, redir->heredoc_delim))
			break ;
		if (redir->heredoc_expand)
			heredoc_line = expander_str(heredoc_line);
		if (ft_putendl_fd(heredoc_line, redir->fd) < 0)
		{
			(ft_free(STR, &heredoc_line), ft_close(redir->fd));
			minishell_exit(1, NULL);
		}
		ft_free(STR, &heredoc_line);
		data(GET)->line_num++;
	}
	ft_free(STR, &heredoc_line);
}

void	heredoc_handle(t_redir *redir)
{
	redir->file_name = heredoc_get_name();
	if (!redir->file_name)
		minishell_exit(1, NULL);
	redir->fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (redir->fd == -1)
		minishell_exit(1, NULL);
	heredoc_feed(redir);
	ft_close(redir->fd);
	return ;
}
