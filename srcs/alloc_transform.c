/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:20:29 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/23 17:17:55 by ldevelle         ###   ########.fr       */
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
	first_size = align_size(HDR_TYPE_TINY, first_size);
	if (first_size + sizeof(*alloc) < old_size && (alloc->flags & HDR_AVAILABLE))
	{
		retval = SUCCESS;
		// mem_index_del(alloc);
		old_flags = alloc->flags;

		alloc_header_init(alloc, first_size + sizeof(*alloc), alloc->size_prev,
			flag_set_pos(old_flags, old_flags & HDR_POS_FIRST));

		new_alloc = alloc_access_next(alloc);
		alloc_header_init(new_alloc, old_size - first_size, first_size - sizeof(*alloc),
			flag_set_pos(old_flags, old_flags & HDR_POS_LAST));

		alloc_update_size_next(new_alloc);
		// mem_index_add(alloc);
		// mem_index_add(new_alloc);
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

int8_t			alloc_join(t_alloc_header *alloc, uint8_t join_with_next)
{
	t_alloc_header		*del_alloc;
	int8_t				retval;
	size_t				new_size;
	size_t				size_prev;
	uint8_t				flags;

	retval = ERROR;
	if (join_with_next == TRUE)
		del_alloc = alloc_access_next(alloc);
	else
		del_alloc = alloc_access_prev(alloc);
	if (del_alloc && del_alloc->flags & HDR_AVAILABLE && alloc->flags & HDR_AVAILABLE)
	{
		new_size = alloc->size + sizeof(*alloc) + del_alloc->size;
		size_prev = (join_with_next == TRUE) ? alloc->size_prev : del_alloc->size_prev;
		flags = alloc_join_get_pos_flags(alloc, del_alloc, join_with_next);
		alloc_header_init(alloc, new_size, size_prev, flags);
		alloc_update_size_next(alloc);
		retval = SUCCESS;
	}
	return (retval);
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
