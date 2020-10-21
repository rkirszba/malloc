/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:20:29 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/21 15:00:12 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

/*
**	This function return the following allocation.
**	This function is notprotected, and can give not owned memory address.
*/

t_alloc			*alloc_access_next(t_alloc *alloc)
{
	t_alloc		*next_alloc;

	next_alloc = (t_alloc*)((uint8_t*)alloc + alloc->size + sizeof(*alloc));
	return (next_alloc);
}

t_alloc			*alloc_access_th(t_zone *zone, size_t zone_size,
				size_t umpteenth)
{
	t_alloc		*alloc;
	void		*ptr_lim;
	size_t		alloc_nb;

	alloc_nb = 0;
	ptr_lim = (uint8_t*)zone + zone_size;
	alloc = &zone->allocation;
	while (alloc_nb < umpteenth)
	{
		alloc = alloc_access_next(alloc);
		if ((void*)alloc >= ptr_lim)
			return (NULL);
		alloc_nb++;
	}
	return (alloc);
}

int8_t			alloc_split(t_alloc *alloc, size_t first_alloc_size)
{
	int8_t		retval;
	size_t		old_size;

	retval = ERROR;
	old_size = ABS(alloc->size);
	if (first_alloc_size < old_size - sizeof(*alloc))
	{
		retval = SUCCESS;
		mem_index_del(alloc);
		alloc->size = first_alloc_size;
		alloc = alloc_access_next(alloc);
		alloc->size = old_size - first_alloc_size - sizeof(*alloc);
	}
	return (retval);
}
