/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:30:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/30 18:33:46 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static int8_t	alloc_join_get_pos_flags(t_alloc_header *alloc,
					t_alloc_header *del_alloc)
{
	uint8_t				flags;

	flags = flag_set_pos(alloc->flags, (alloc->flags & HDR_POS_FIRST)
		| (del_alloc->flags & HDR_POS_LAST));
	return (flags);
}

static int8_t		remove_alloc_from_ds(t_alloc_header *alloc)
{
	if (alloc->flags & HDR_AVAILABLE)
		return available_remove(alloc);
	else
		return unavailable_remove(alloc);
}


t_alloc_header	*alloc_join(t_alloc_header *alloc, t_alloc_header *del_alloc)
{
	size_t				new_size;
	size_t				size_prev;
	uint8_t				flags;

	if (alloc && del_alloc)//TODO: rm ?
	{
		new_size = alloc->size + sizeof(*alloc) + del_alloc->size;
		size_prev = alloc->size_prev;
		flags = alloc_join_get_pos_flags(alloc, del_alloc);
		alloc_header_init(alloc, new_size, size_prev, flags);
		return (alloc);
	}
	return (NULL);
}

t_alloc_header	*alloc_join_defrag(t_alloc_header *alloc, int8_t r_left, int8_t r_right)
{
	t_alloc_header		*del_alloc;

	if (NULL == alloc)
		return (NULL);
	del_alloc = alloc_access_next(alloc);
	if (alloc->flags & HDR_AVAILABLE
	&& del_alloc && del_alloc->flags & HDR_AVAILABLE)
	{
		if (TRUE == r_left)
		{
			remove_alloc_from_ds(alloc);//TODO: check return ?
		}
		if (TRUE == r_right)
		{
			remove_alloc_from_ds(del_alloc);//TODO: check return ?
		}
		return (alloc_join(alloc, del_alloc));
	}
	return NULL;
}


t_alloc_header	*alloc_join_realloc(t_alloc_header *alloc, size_t size)
{
	t_alloc_header		*del_alloc;

	if (NULL == alloc)
		return (NULL);
	if (alloc->flags & HDR_TYPE_LARGE && alloc->size < size)
		return (NULL);
	del_alloc = alloc_access_next(alloc);
	if (del_alloc && del_alloc->flags & HDR_AVAILABLE
	&& alloc->size + sizeof(t_alloc_header) + del_alloc->size
	<= align_size(alloc->flags & HDR_TYPE, size))
	{
		remove_alloc_from_ds(del_alloc);//TODO: check return ?
		return (alloc_join(alloc, del_alloc));
	}
	return NULL;
}
