/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:30:55 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/30 17:07:15 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

/*
**	verify that:
**		1st size is >= current size + new header
**		2nd size is at minimum bigger than aligned(smaller_size)
*/

static uint8_t	alloc_split_check_size(t_alloc_header *alloc, size_t first_size)
{
	size_t				old_size;
	long long			second_size;

	old_size = alloc->size;
	// first_size = align_size(alloc->flags & HDR_TYPE, first_size);
	if (first_size + sizeof(*alloc) < old_size)
	{
		second_size = old_size - first_size - sizeof(*alloc);
		// if ((size_t)second_size % 8  != 0)
		// 	printf("Bad aligned size %lu\n", second_size);
		if ((alloc->flags & HDR_TYPE) == HDR_TYPE_TINY)
		{
			if (second_size >= (long long)static_mem()->tiny.alloc_size_min)
				return (TRUE);
		}
		else if ((alloc->flags & HDR_TYPE) == HDR_TYPE_SMALL)
		{
			if (second_size >= (long long)static_mem()->small.alloc_size_min)
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
	size_t				second_size;

	retval = ERROR;
	old_size = alloc->size;
	first_size = align_size(alloc->flags & HDR_TYPE, first_size);
	if (alloc_split_check_size(alloc, first_size))
	{
		retval = SUCCESS;
		old_flags = alloc->flags;

		alloc_header_init(alloc, first_size, alloc->size_prev,
			flag_set_pos(old_flags, old_flags & HDR_POS_FIRST));

		new_alloc = alloc_access_next(alloc);
		// if ((size_t)new_alloc % 8  != 0)
		// 	printf("Bad aligned %p\n", new_alloc);
		second_size = old_size - first_size - sizeof(*alloc);
		alloc_header_init(new_alloc,
			second_size, first_size,
			flag_set_pos(old_flags, old_flags & HDR_POS_LAST));
		alloc_set_available(new_alloc);
	}
	return (retval);
}

int8_t			alloc_split_malloc(t_alloc_header *alloc, size_t first_size)
{
	int8_t				retval;

	retval = ERROR;
	if (alloc->flags & HDR_AVAILABLE)
	{
		retval = alloc_split(alloc, first_size);
	}
	return (retval);
}
