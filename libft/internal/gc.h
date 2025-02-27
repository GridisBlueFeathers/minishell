/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:37:06 by svereten          #+#    #+#             */
/*   Updated: 2025/02/11 13:32:59 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef GC_H
# define GC_H

typedef enum e_option
{
	GET,
	FREE,
}	t_option;

typedef enum e_gc_node_type
{
	FD,
	PTR
}	t_gc_node_type;

typedef union u_data
{
	int		fd;
	void	*ptr;
}	t_data;

typedef struct s_gc_node
{
	t_data				data;
	t_gc_node_type		type;
	struct s_gc_node	*next;
	struct s_gc_node	*prev;
}	t_gc_node;

typedef struct s_gc_data
{
	t_gc_node	*head;
	t_gc_node	*tail;
	int			amount;
}	t_gc_data;

t_gc_data	*gc(t_option op);

int			gc_data_add(t_gc_node_type t, t_data data);
void		gc_data_remove(t_gc_node_type t, t_data data);

#endif
