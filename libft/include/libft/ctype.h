/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctype.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:30:33 by svereten          #+#    #+#             */
/*   Updated: 2025/02/21 18:56:49 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CTYPE_H
# define CTYPE_H

/* libc copies */

//
int	ft_isalnum(int c);
int	ft_isprint(int c);
int	ft_isdigit(int c);
int	ft_isascii(int c);
int	ft_isalpha(int c);
int	ft_isspace(int c);

# define LLONG_MAX_STR "9223372036854775807"
# define LLONG_MIN_STR "9223372036854775808"

/* libft */

//
int	ft_isnumber(char *str);

#endif
