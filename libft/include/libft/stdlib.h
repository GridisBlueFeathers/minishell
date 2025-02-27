/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdlib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:52:44 by svereten          #+#    #+#             */
/*   Updated: 2025/01/11 15:43:26 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef STDLIB_H
# define STDLIB_H

# include <stdlib.h>

typedef enum e_type
{
	STR,
	STRUCT,
	STR_ARR,
}	t_type;

# ifndef PANIC_MSG
#  define PANIC_MSG "libft"
# endif

/* libc copies */

//
int		ft_atoi(const char *number);
/**
 * Mimics `calloc`
 *
 * Protected against and overflows 0 in arguments
 *
 * Adds returned pointer to garbage collector
 */
void	*ft_calloc(size_t nmemb, size_t size);
/**
 * Exits program and triggers garbage collector to collect memory and fds
 */
void	ft_exit(int status);
/**
 * Frees variable and sets it to NULL, variable should be passed by reference
 *
 * Removes pointer from being tracked by garbage collector
 */
void	ft_free(t_type type, void *ref);

/* libft */

//
int		ft_atoi_check(char *number, int *res);
char	*ft_itoa(int n);
void	ft_panic(int status, char *msg);

#endif 
