/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:20:29 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/22 14:37:43 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	alloc_header_init(t_alloc_header *header, size_t size,
		uint8_t available, uint8_t last)
{
	header->size = size - sizeof(header);
	header->available = available;
	header->last = last;
}

/*
**	This function return the following allocation.
**	This function is not protected, and can give not owned memory address.
*/

t_alloc_header			*alloc_access_next(t_alloc_header *alloc)
{
	t_alloc_header		*next_alloc_header;

	next_alloc_header = (t_alloc_header*)((uint8_t*)alloc + alloc->size + sizeof(*alloc));
	return (next_alloc_header);
}

t_alloc_header			*alloc_access_th(t_zone *zone, size_t zone_size,
				size_t umpteenth)
{
	t_alloc_header		*alloc;
	void		*ptr_lim;
	size_t		alloc_nb;

	alloc_nb = 0;
	ptr_lim = (uint8_t*)zone + zone_size;
	alloc = &zone->first_alloc_header;
	while (alloc_nb < umpteenth)
	{
		if (alloc->last)
			return (NULL);
		alloc = alloc_access_next(alloc);
		if ((void*)alloc >= ptr_lim)
			return (NULL);
		alloc_nb++;
	}
	return (alloc);
}

int8_t			alloc_split(t_alloc_header *alloc, size_t first_alloc_header_size)
{
	t_alloc_header		*new_alloc;
	int8_t		retval;
	size_t		old_size;

	retval = ERROR;
	old_size = ABS(alloc->size);
	if (first_alloc_header_size < old_size - sizeof(*alloc))
	{
		retval = SUCCESS;
		mem_index_del(alloc);
		alloc->size = first_alloc_header_size;
		new_alloc = alloc_access_next(alloc);
		new_alloc->size = old_size - first_alloc_header_size - sizeof(*alloc);
		mem_index_add(alloc);
		mem_index_add(new_alloc);
	}
	return (retval);
}
