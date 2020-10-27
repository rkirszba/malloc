/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:27:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/27 15:30:14 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
/*
**	Defragment elem:	[prev]	[x]	[next]
**	
**	Prev is true, when the alloc_header sent by defragment correspond to [prev].
*/

t_alloc_header	*defrag_elem(t_alloc_header *alloc_header, int8_t prev)
{
	//t_rbt  			**tree;
	t_alloc_header	*new;
	t_alloc_header	*old;

	if (NULL != alloc_header)
	{
		old = alloc_access_next(alloc_header);
		if (NULL != (new = alloc_join_defrag(alloc_header, prev, !prev)))
			alloc_header = new;
	}
	return (alloc_header);
}

/*
**	Defragment:	[a]	[x]	[a]
**	
**	For the given [x] space, defragment will try to join it with its right, 
**	then left neighbour.
**	During this process defragment will take care to remove left and right
**	element from their corresponding (un)available tree(s)
**	It will not do the same for the element in the middle, which it leaves the
**	duty to manage to the caller.
*/

t_alloc_header	*defragment(t_alloc_header *alloc_header)
{
	t_alloc_header	*new;
	
	alloc_header = defrag_elem(alloc_header, FALSE);
	if (NULL != (new = alloc_access_prev(alloc_header)))
	{
		alloc_header = defrag_elem(new, TRUE);
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
	alloc_header = defragment(alloc_header);
	print_alloc(alloc_header);
	if (TRUE == can_zone_liberate(alloc_header))
	{
		zone_liberate(alloc_access_zone(alloc_header));
	}
	else
	{
		available_add(alloc_header);
	}
}
