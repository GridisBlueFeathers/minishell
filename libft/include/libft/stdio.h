/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:40:28 by svereten          #+#    #+#             */
/*   Updated: 2024/11/26 16:13:28 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STDIO_H
# define STDIO_H

# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>

/* libc copies */

//
int		ft_printf(const char *fmt, ...);
int		ft_dprintf(int fd, const char *fmt, ...);

/* libft */

//
/**
 * `fmt` accepts either 'x' or 'X' to output lowercase or uppercase hex number
 */
int		ft_putuhex_fd(unsigned long n, int fd, char fmt);
int		ft_putuint_fd(unsigned int n, int fd);
int		ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);
void	ft_putstrarr_fd(char **arr, int fd);

#endif
