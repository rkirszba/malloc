/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:27:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/23 15:40:54 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


t_alloc_header	*get_alloc_header(void* alloc, t_zone *zone)
{
	t_alloc_header	*alloc_cursor;

	while (zone)
	{
		alloc_cursor = &zone->first_alloc_header;
		while (alloc_cursor)
		{
			if ((void*)alloc_cursor == (uint8_t*)alloc - (sizeof(t_alloc_header))
				&& alloc_cursor->flags & HDR_AVAILABLE)
			{
				return alloc_cursor;
			}
			alloc_cursor = alloc_access_next(alloc_cursor);
		}
		zone = zone->header.next_zone;
	}
	return NULL;
}

void	free_alloc(t_alloc_header *header)
{
	header->flags = flag_set_availabilty(header->flags, HDR_AVAILABLE);
}

void	our_free(void *alloc)
{
	t_infos			*base;
	t_alloc_header	*alloc_header;

	base = static_mem();
	if (!(alloc_header = get_alloc_header(alloc, base->tiny.zone)))
		if (!(alloc_header = get_alloc_header(alloc, base->small.zone)))
			return;
	free_alloc(alloc_header);
}

/*
int8_t	remove_alloc(t_bst ***tree, )
{

}

void	our_free(void *alloc)
{
	t_malloc		*base;
	t_alloc_header	*alloc_header;

	base = *static_mem();
	if (remove_alloc(base->alloc_tab, alloc) == FAILURE)
		return ;
	alloc_header = (t_alloc_header*)alloc - sizeof(t_alloc_header);
	alloc_header->available = TRUE;

}

*/
