/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:27:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/22 15:08:08 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


void	*get_alloc_header(void* alloc, t_zone *zone)
{
	t_alloc_header	*alloc_cursor;

	while (zone)
	{
		alloc_cursor = &zone->first_alloc_header;
		while (TRUE)
		{
			if ((void*)alloc_cursor == alloc - sizeof(t_zone_header)
				&& alloc_cursor->available == FALSE)
				return alloc_cursor;
			if (alloc_cursor->last == FALSE)
				alloc_cursor += sizeof(t_zone_header) + alloc_cursor->size;
			else
				break ;	
		}
		zone = zone->header.next_zone;
	}
	return NULL;
}

void	free_alloc(t_alloc_header *alloc_header)
{
	alloc_header->available == TRUE;
}

void	our_free(void *alloc)
{
	t_malloc	*base;
	void		*alloc_header;

	base = *static_mem();
	if (!(alloc_header = get_alloc_header(alloc, base->tiny_zone)))
		if (!(alloc_header = get_alloc_header(alloc, base->small_zone)))
			return;
	free_alloc(alloc_header);
}
