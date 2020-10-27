/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:27:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/27 18:07:56 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void			defrag_elem_right(t_alloc_header *alloc_header)
{
	if (NULL != alloc_header)
		alloc_join_defrag(alloc_header, FALSE, TRUE);

}

t_alloc_header	*defrag_elem_left(t_alloc_header *middle)
{
	t_alloc_header	*left;
	t_alloc_header	*joined;

	left = alloc_access_prev(middle);
	if (NULL != left)
	{
		joined = alloc_join_defrag(left, TRUE, FALSE);
		if (NULL != joined)
			return (joined);
	}
	return (middle);
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
	defrag_elem_right(alloc_header);	
	alloc_header = defrag_elem_left(alloc_header);
	// printf("2%s flag av %d\n", __func__, alloc_header->flags & HDR_AVAILABLE);
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
	// printf("%s flag av %d\n", __func__, alloc_header->flags & HDR_AVAILABLE);
	if (TRUE == can_zone_liberate(alloc_header))
	{
		zone_liberate(alloc_access_zone(alloc_header));
	}
	else
	{
		available_add(alloc_header);
	}
}
