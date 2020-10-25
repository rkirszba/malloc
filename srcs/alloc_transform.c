/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:20:29 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/25 02:27:28 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

size_t			align_size(uint8_t type_flag, size_t size)
{
	if (type_flag & HDR_TYPE_TINY)
		size = (((size - 1) >> 4) << 4) + 16;
	if (type_flag & HDR_TYPE_SMALL)
		size = (((size - 1) >> 9) << 9) + 512;
	if (type_flag & HDR_TYPE_LARGE)
		size = (((size - 1) >> 12) << 12) + 4096;
	return (size);
}


size_t			secure_align_size(size_t size)
{
	t_infos			*base;
	size_t			aligned_size;

	base = static_mem();
	aligned_size = align_size(HDR_TYPE_TINY, size);
	if (aligned_size < base->tiny.alloc_size_max)
		return (aligned_size);
	aligned_size = align_size(HDR_TYPE_SMALL, size);
	if (aligned_size < base->small.alloc_size_max)
		return (aligned_size);
	return (align_size(HDR_TYPE_LARGE, size));
}
/*
**	verify that:
**		1st size is >= current size + new header
**		2nd size is at minimum bigger than aligned(smaller_size)
*/

static uint8_t	alloc_split_check_size(t_alloc_header *alloc, size_t first_size)
{
	size_t				old_size;
	size_t				second_size;

	old_size = alloc->size;
	first_size = align_size(alloc->flags & HDR_TYPE, first_size);
	if (first_size + sizeof(*alloc) < old_size)
	{
		second_size = old_size - first_size - sizeof(*alloc);
		if ((alloc->flags & HDR_TYPE) == HDR_TYPE_TINY)
		{
			if (second_size >= static_mem()->tiny.alloc_size_min)
				return (TRUE);
		}
		else if ((alloc->flags & HDR_TYPE) == HDR_TYPE_SMALL)
		{
			if (second_size >= static_mem()->small.alloc_size_min)
				return (TRUE);
		}
	}
	return (FALSE);
}
/*
**	This function takes the size of the first part in partameter.
**	This size will be aligned before splitting.
*/

int8_t			alloc_split(t_alloc_header *alloc, size_t first_size)
{
	t_alloc_header		*new_alloc;
	int8_t				retval;
	int8_t				old_flags;
	size_t				old_size;

	retval = ERROR;
	old_size = alloc->size;
	first_size = align_size(alloc->flags & HDR_TYPE, first_size);
	if (alloc_split_check_size(alloc, first_size)
	&& (alloc->flags & HDR_AVAILABLE))
	{
		retval = SUCCESS;
		old_flags = alloc->flags;

		alloc_header_init(alloc, first_size + sizeof(*alloc), alloc->size_prev,
			flag_set_pos(old_flags, old_flags & HDR_POS_FIRST));

		new_alloc = alloc_access_next(alloc);
		alloc_header_init(new_alloc,
			old_size - first_size, first_size - sizeof(*alloc),
			flag_set_pos(old_flags, old_flags & HDR_POS_LAST));

		alloc_update_size_next(new_alloc);
	}
	return (retval);
}

static int8_t	alloc_join_get_pos_flags(t_alloc_header *alloc,
					t_alloc_header *del_alloc, uint8_t is_next)
{
	uint8_t				flags;

	if (is_next == TRUE)
	{
		flags = flag_set_pos(alloc->flags, (alloc->flags & HDR_POS_FIRST)
			| (del_alloc->flags & HDR_POS_LAST));
	}
	else
	{
		flags = flag_set_pos(alloc->flags, (del_alloc->flags & HDR_POS_FIRST)
			| (alloc->flags & HDR_POS_LAST));
	}
	return (flags);
}

t_alloc_header	*alloc_join(t_alloc_header *alloc, uint8_t join_with_next)
{
	t_alloc_header		*del_alloc;
	size_t				new_size;
	size_t				size_prev;
	uint8_t				flags;

	if (join_with_next == TRUE)
		del_alloc = alloc_access_next(alloc);
	else
		del_alloc = alloc_access_prev(alloc);
	if (alloc && del_alloc
	&& del_alloc->flags & HDR_AVAILABLE && alloc->flags & HDR_AVAILABLE)
	{
		new_size = alloc->size + sizeof(*alloc) + del_alloc->size;
		size_prev = (join_with_next == TRUE) ? alloc->size_prev : del_alloc->size_prev;
		flags = alloc_join_get_pos_flags(alloc, del_alloc, join_with_next);
		alloc_header_init(alloc, new_size, size_prev, flags);
		alloc_update_size_next(alloc);
		return (join_with_next == TRUE) ? alloc : del_alloc;
	}
	return (NULL);
}



void		*get_spot(size_t size_to_find)
{
	t_alloc_header	*alloc;
	t_zone			*zone;

	// size_to_find = (((size_to_find - 1) >> 4) << 4) + 16;
	zone = static_mem()->tiny.zone;
	while (zone)
	{
		alloc = &zone->first_alloc_header;
		while (alloc)
		{
			if ((alloc->flags & HDR_AVAILABLE))
			{
				if ((size_t)alloc->size >= size_to_find)
				{
					alloc_split(alloc, size_to_find);
					alloc->flags = flag_set_availabilty(alloc->flags, 0);
					return ((uint8_t*)alloc + sizeof(*alloc));
				}
			}
			alloc = alloc_access_next(alloc);
		}
		zone = zone->header.next_zone;
	}
	return (NULL);
}

/*
**	SEARCH IN TAB FIRST MATCHING SIZE;
**	get_first_matching_available_tree();
**	remove elem from available
**	if split(elem)
**		save in available alloc_access_next(elem)
**	elem save in unavailable()
**	save with address of header : get_unavailable_tree()
**	*tree = tree_insert_func_ll(*tree, &alloc_header->rbt, (void*)alloc_header, &compare_adresses);
*/

t_alloc_header		*alloc_get(size_t size)
{
	t_alloc_header	*alloc;
	t_rbt   		**tree;
	t_rbt			*node;
	int				umpteenth_node;

	printf("~~~Hey\n");
	printf("~~~Asking for size %lu\n", size);
	size = secure_align_size(size);
	printf("~~~Aligned size is %lu\n", size);
	if (NULL == (tree = available_get_tree_with_memory(size)))
		return (NULL);
	umpteenth_node = 0;
	printf("~~~Wassup, tree %p\n", *tree);
	if (!(node = tree_get_node_th(*tree, &umpteenth_node)))
	{
		dprintf(2, "Error: can't get %dth node of tree\n", umpteenth_node);
		return (NULL);
	}
	printf("~~~We got node %p to give\n", node);
	alloc = (t_alloc_header*)node;
	printf("~~~It's size is %d\n", alloc->size);
	available_remove(alloc);
	printf("~~~It's size is %d bef split\n", alloc->size);
	if (SUCCESS == alloc_split(alloc, size))
	{
		printf("~~~We splitted !\n");
		available_add(alloc_access_next(alloc));
	}
	else
		printf("~~~No split !\n");
	printf("~~~It's size is %d aft split\n", alloc->size);
	alloc_set_unavailable(alloc);
	unavailable_add(alloc);
	return (alloc);
}
