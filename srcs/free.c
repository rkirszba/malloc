/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:27:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 02:35:23 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

// t_alloc_header	*defragment(t_alloc_header *alloc_header)
// {
// 	t_rbt  			**tree;
// 	t_alloc_header	*old;
// 	t_alloc_header	*save;
//
// 	old = alloc_access_next(alloc_header);
// 	if (alloc_header && alloc_join(alloc_header, TRUE))
// 	{
// 		tree = unavailable_get_tree(old);
// 		*tree = tree_delete_node(&old->rbt);
// 	}
// 	print_malloc_mem();
//
// 	save = alloc_header;
// 	old = alloc_access_prev(alloc_header);
// 	if (old && (old = alloc_join(old, TRUE)))
// 	{
// 		tree = unavailable_get_tree(alloc_header);
// 		*tree = tree_delete_node(&alloc_header->rbt);
// 	}
// 	else
// 		return (save);
// 	return (old);
// }

t_alloc_header	*defragment(t_alloc_header *alloc_header)
{
	t_alloc_header	*neighbor;

	neighbor = alloc_access_next(alloc_header);
	if (neighbor && neighbor->flags & HDR_AVAILABLE)
	{
		alloc_header = alloc_join(alloc_header, TRUE);
		tree_delete_one_child(&neighbor->rbt);
		return (defragment(alloc_header));
	}
	neighbor = alloc_access_prev(alloc_header);
	if (neighbor && neighbor->flags & HDR_AVAILABLE)
	{
		alloc_header = alloc_join(neighbor, TRUE);
		tree_delete_one_child(&neighbor->rbt);
	}
	return (alloc_header);
}


void		our_free(void *ptr)
{
	t_alloc_header	*alloc_header;

	if (static_mem()->is_init != TRUE)
		return ;
	alloc_header = ptr - sizeof(t_alloc_header);
	if (unavailable_remove((void*)alloc_header) == FAILURE)
		return ;
	alloc_set_available(alloc_header);
	// alloc_header = defragment(alloc_header);
	available_add(alloc_header);
}
