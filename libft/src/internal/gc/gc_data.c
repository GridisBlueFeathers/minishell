/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:41:45 by svereten          #+#    #+#             */
/*   Updated: 2025/01/11 17:19:07 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "gc.h"
#include "internal.h"

int	gc_data_add(t_gc_node_type t, t_data data)
{
	t_gc_node	*node;

	node = (t_gc_node *)ft_calloc_no_gc(1, sizeof(t_gc_node));
	if (!node)
		return (0);
	node->type = t;
	if (t == PTR)
		node->data.ptr = data.ptr;
	else
		node->data.fd = data.fd;
	gc(GET)->amount++;
	if (gc(GET)->tail)
	{
		node->prev = gc(GET)->tail;
		gc(GET)->tail->next = node;
		gc(GET)->tail = node;
		return (1);
	}
	gc(GET)->head = node;
	gc(GET)->tail = node;
	return (1);
}

static void	gc_data_pop(t_gc_node *node)
{
	gc(GET)->amount--;
	if (node->prev)
		node->prev->next = node->next;
	else
		gc(GET)->head = node->next;
	if (node->next)
		node->next->prev = node->prev;
	else
		gc(GET)->tail = node->prev;
	free(node);
}

void	gc_data_remove(t_gc_node_type t, t_data data)
{
	t_gc_node	*cur;

	cur = gc(GET)->head;
	while (cur)
	{
		if ((t == PTR && data.ptr == cur->data.ptr)
			|| (t == FD && data.fd == cur->data.fd))
		{
			gc_data_pop(cur);
			return ;
		}
		cur = cur->next;
	}
}
