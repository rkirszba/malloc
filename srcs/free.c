/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:27:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 16:53:06 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_alloc_header	*defrag_elem(t_alloc_header *alloc_header)
{
	t_rbt  			**tree;
	t_alloc_header	*new;
	t_alloc_header	*old;

	if (NULL == alloc_header)
		return (alloc_header);
	old = alloc_access_next(alloc_header);
	if (NULL != (new = alloc_join(alloc_header)))
	{
		tree = unavailable_get_tree(old);
		*tree = tree_delete_node(&old->rbt);
		alloc_header = new;
	}
	return (alloc_header);
}

t_alloc_header	*defragment(t_alloc_header *alloc_header)
{
	t_alloc_header	*new;

	alloc_header = defrag_elem(alloc_header);
	if (NULL != (new = alloc_access_prev(alloc_header)))
		alloc_header = defrag_elem(new);
	return (alloc_header);
}

// t_alloc_header	*defragment(t_alloc_header *alloc_header)
// {
// 	t_alloc_header	*neighbor;
//
// 	neighbor = alloc_access_next(alloc_header);
// 	if (neighbor && neighbor->flags & HDR_AVAILABLE)
// 	{
// 		alloc_header = alloc_join(alloc_header);
// 		tree_delete_one_child(&neighbor->rbt);
// 		return (defragment(alloc_header));
// 	}
// 	neighbor = alloc_access_prev(alloc_header);
// 	if (neighbor && neighbor->flags & HDR_AVAILABLE)
// 	{
// 		alloc_header = alloc_join(neighbor);
// 		tree_delete_one_child(&neighbor->rbt);
// 	}
// 	return (alloc_header);
// }


void		our_free(void *ptr)
{
	t_alloc_header	*alloc_header;

	if (static_mem()->is_init != TRUE)
		return ;
	alloc_header = ptr - sizeof(t_alloc_header);
	if (unavailable_remove((void*)alloc_header) == FAILURE)
		return ;
	alloc_set_available(alloc_header);
	alloc_header = defragment(alloc_header);
	if (TRUE == can_zone_liberate(alloc_header))
		zone_liberate(alloc_access_zone(alloc_header));
	else
		available_add(alloc_header);
}
