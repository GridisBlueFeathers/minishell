/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:37:11 by svereten          #+#    #+#             */
/*   Updated: 2025/02/10 15:39:57 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <dirent.h>

int	is_directory(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
		return (closedir(dir), 1);
	return (0);
}
