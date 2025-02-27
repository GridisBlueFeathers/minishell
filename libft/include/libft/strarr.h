/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strarr.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:17:53 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 16:21:24 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STRARR_H
# define STRARR_H

# include <stddef.h>

/**
 * Compares string arrays by full size
 *
 * If both are NULL returns 1 anyway
 */
int		ft_strarrcmp(char **arr1, char **arr2);
/**
 * Duplicates string array
 *
 * Protected: returns NULL in case of NULL
 */
char	**ft_strarrdup(char **arr);
/**
 * Counts strings in string array
 * 
 * Protected: returns 0 in case of NULL
 */
size_t	ft_strarrlen(char **arr);

#endif
