/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:11:11 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 16:14:05 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INTERNAL_H
# define INTERNAL_H

# include "libft/libft.h"

void	libft_init(void) __attribute__ ((constructor(1)));
void	*ft_calloc_no_gc(size_t nmemb, size_t size);
int		ft_putaddr_fd(void *p, int fd);

#endif
