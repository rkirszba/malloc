/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:30:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/30 17:44:50 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static int8_t	alloc_join_get_pos_flags(t_alloc_header *alloc,
					t_alloc_header *del_alloc)
{
	uint8_t				flags;

	// printf("alloc %d del_alloc %d\n", alloc->flags & HDR_AVAILABLE, del_alloc->flags & HDR_AVAILABLE);
	flags = flag_set_pos(alloc->flags, (alloc->flags & HDR_POS_FIRST)
		| (del_alloc->flags & HDR_POS_LAST));
	// printf("Res: %d\n", flags & HDR_AVAILABLE);
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

	// if (alloc->flags & HDR_AVAILABLE
	// && del_alloc && del_alloc->flags & HDR_AVAILABLE)
	if (alloc && del_alloc)//TODO: rm ?
	{
		//if (FAILURE == available_remove(del_alloc))
		//	return NULL;
		new_size = alloc->size + sizeof(*alloc) + del_alloc->size;
		size_prev = alloc->size_prev;
		flags = alloc_join_get_pos_flags(alloc, del_alloc);
		alloc_header_init(alloc, new_size, size_prev, flags);
		// printf("%s flag av %d\n", __func__, alloc->flags & HDR_AVAILABLE);
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
	// printf("%s left:%d right:%d\n", __func__, r_left, r_right);
	if (alloc->flags & HDR_AVAILABLE
	&& del_alloc && del_alloc->flags & HDR_AVAILABLE)
	{
		if (TRUE == r_left)
		{
			// printf("TRYING TO REMOVE LEFT\n");
			remove_alloc_from_ds(alloc);//TODO: check return ?
		}
		if (TRUE == r_right)
		{
			// printf("TRYING TO REMOVE RIGHT\n");
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
	if (alloc->flags & HDR_TYPE_LARGE && alloc->size < size) //pourquoi la deuxieme verif?
		return (NULL);
	del_alloc = alloc_access_next(alloc);
	printf("del alloc = %p\n", del_alloc);
	if (del_alloc && del_alloc->flags & HDR_AVAILABLE
	&& alloc->size + sizeof(t_alloc_header) + del_alloc->size >= size)
	{
		remove_alloc_from_ds(del_alloc);//TODO: check return ?
		return (alloc_join(alloc, del_alloc));
	}
	printf("JOIN FAILED\n");
	return NULL;
}
