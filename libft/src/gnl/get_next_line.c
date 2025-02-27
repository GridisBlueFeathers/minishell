/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 12:34:26 by svereten          #+#    #+#             */
/*   Updated: 2024/09/24 12:06:05 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft/get_next_line.h"

static char	*get_next_output(char *fd_buf, int *check)
{
	char	*res;
	char	*nl_location;
	size_t	len;

	if (!fd_buf)
		return (NULL);
	nl_location = ft_strchr(fd_buf, '\n');
	if (!nl_location)
	{
		res = ft_substr(fd_buf, 0, ft_strlen(fd_buf));
		if (!res)
			*check = 0;
		if (!res || !ft_strlen(res))
			return (free(res), NULL);
		return (res);
	}
	len = nl_location - fd_buf + 1;
	res = ft_substr(fd_buf, 0, len);
	if (!res)
		*check = 0;
	return (res);
}

static char	*remove_output(char *fd_buf, char **aux_buf, int *check)
{
	char	*res;
	char	*nl_location;
	size_t	nnl_index;

	if (!fd_buf)
		return (NULL);
	if (!*aux_buf)
		return (ft_free(STR, &fd_buf), NULL);
	nl_location = ft_strchr(fd_buf, '\n');
	if (!nl_location || !nl_location[1])
		return (ft_free(STR, &fd_buf), NULL);
	nnl_index = nl_location - fd_buf;
	res = ft_substr(fd_buf, nnl_index + 1, ft_strlen(fd_buf) - nnl_index - 1);
	if (!res)
	{
		ft_free(STR, aux_buf);
		*check = 0;
	}
	return (ft_free(STR, &fd_buf), res);
}

int	get_next_line(int fd, char **line)
{
	static char	*fd_buf[MAX_FD];
	char		*aux_buf;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	aux_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!aux_buf || !line)
		return (free(aux_buf), ft_free(STR, &fd_buf[fd]), 0);
	bytes_read = 1;
	while (!ft_strchr(fd_buf[fd], '\n') && bytes_read)
	{
		bytes_read = read(fd, aux_buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(aux_buf), ft_free(STR, &fd_buf[fd]), 0);
		aux_buf[bytes_read] = '\0';
		fd_buf[fd] = ft_strjoin(fd_buf[fd], aux_buf);
		if (!fd_buf[fd])
			return (free(aux_buf), 0);
	}
	free(aux_buf);
	bytes_read = 1;
	aux_buf = get_next_output(fd_buf[fd], &bytes_read);
	fd_buf[fd] = remove_output(fd_buf[fd], &aux_buf, &bytes_read);
	return (*line = aux_buf, bytes_read);
}
