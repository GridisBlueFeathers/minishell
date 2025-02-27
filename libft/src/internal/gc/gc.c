/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svereten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:10:45 by svereten          #+#    #+#             */
/*   Updated: 2025/02/26 11:33:40 by svereten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "internal.h"
#include "gc.h"
#include "libft/libft.h"

__attribute__((constructor))
static	void	gc_start(void)
{
	if (gc(GET) == NULL)
		exit(1);
}

static t_gc_data	*gc_init(void)
{
	t_gc_data	*res;

	res = (t_gc_data *)ft_calloc_no_gc(1, sizeof(t_gc_data));
	return (res);
}

static void	gc_free(t_gc_data *gc)
{
	t_gc_node	*cur;
	t_gc_node	*tmp;

	cur = gc->head;
	while (cur)
	{
		tmp = cur->next;
		if (cur->type == FD)
			close(cur->data.fd);
		else
			free(cur->data.ptr);
		free(cur);
		cur = tmp;
	}
	free(gc);
}

t_gc_data	*gc(t_option op)
{
	static t_gc_data	*gc;

	if (op == GET)
	{
		if (!gc)
			gc = gc_init();
		return (gc);
	}
	if (op == FREE)
	{
		gc_free(gc);
		gc = NULL;
		return (NULL);
	}
	return (NULL);
}
