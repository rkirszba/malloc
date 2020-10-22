/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:59:00 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/22 14:38:35 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	zone_header_init(t_zone_header *header)
{
	header->next_zone = NULL;
}

/*
**	This function create a zone of allocation of size 'zone_size' at the end of
**	the zone linked list.
**	It then adds a new entry available memory index
*/

int8_t	zone_create(t_zone **zone, size_t zone_size)
{
	t_zone			*zone_prev;

	zone_prev = *zone;
	while (*zone)
	{
		zone_prev = *zone;
		*zone = (*zone)->header.next_zone;
	}

	*zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (*zone == MAP_FAILED)
		return (ERROR);

	if (zone_prev)
		zone_prev->header.next_zone = (*zone);

	zone_header_init(&(*zone)->header);
	alloc_header_init(&(*zone)->first_alloc_header, zone_size - sizeof((*zone)->header), TRUE, TRUE);

	//add_available_alloc((*zone)->allocation, (*zone)->allocation.size);
	return (SUCCESS);
}


int8_t	zone_liberate_all(t_zone *zone, size_t zone_size)
{
	t_zone			*n_zone;
	int8_t			retval;

	retval = SUCCESS;
	while (zone)
	{
		n_zone = zone;
		zone = zone->header.next_zone;
	    if (-1 == munmap((void*)n_zone, zone_size))
			retval = ERROR;
	}
	return (retval);
}
