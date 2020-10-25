/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:20:29 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/25 13:09:43 by ezalos           ###   ########.fr       */
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
	if (aligned_size <= base->small.alloc_size_max)
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

		alloc_header_init(alloc, first_size, alloc->size_prev,
			flag_set_pos(old_flags, old_flags & HDR_POS_FIRST));

		new_alloc = alloc_access_next(alloc);
		alloc_header_init(new_alloc,
			old_size - first_size - sizeof(*alloc), first_size,
			flag_set_pos(old_flags, old_flags & HDR_POS_LAST));
	}
	return (retval);
}

static int8_t	alloc_join_get_pos_flags(t_alloc_header *alloc,
					t_alloc_header *del_alloc)
{
	uint8_t				flags;

	flags = flag_set_pos(alloc->flags, (alloc->flags & HDR_POS_FIRST)
		| (del_alloc->flags & HDR_POS_LAST));
	return (flags);
}

t_alloc_header	*alloc_join(t_alloc_header *alloc)
{
	t_alloc_header		*del_alloc;
	size_t				new_size;
	size_t				size_prev;
	uint8_t				flags;

	if (NULL == alloc)
		return (NULL);
	del_alloc = alloc_access_next(alloc);
	if (alloc->flags & HDR_AVAILABLE
	&& del_alloc && del_alloc->flags & HDR_AVAILABLE)
	{
		new_size = alloc->size + sizeof(*alloc) + del_alloc->size;
		size_prev = alloc->size_prev;
		flags = alloc_join_get_pos_flags(alloc, del_alloc);
		alloc_header_init(alloc, new_size - sizeof(*alloc), size_prev, flags);
		return (alloc);
	}
	return (NULL);
}

t_alloc_header		*alloc_get(size_t size)
{
	t_alloc_header	*alloc;
	t_rbt   		**tree;
	t_rbt			*node;
	int				umpteenth_node;

	size = secure_align_size(size);
	if (NULL == (tree = available_get_tree_with_memory(size)))
		return (NULL);
	umpteenth_node = 0;
	if (!(node = tree_get_node_th(*tree, &umpteenth_node)))
	{
		dprintf(2, "Error: can't get %dth node of tree\n", umpteenth_node);
		return (NULL);
	}
	alloc = (t_alloc_header*)node;
	available_remove(alloc);
	if (SUCCESS == alloc_split(alloc, size))
		available_add(alloc_access_next(alloc));
	alloc_set_unavailable(alloc);
	unavailable_add(alloc);
	return (alloc);
}
