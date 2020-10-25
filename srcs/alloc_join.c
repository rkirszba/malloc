/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_join.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:30:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 15:30:30 by ezalos           ###   ########.fr       */
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
