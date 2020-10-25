/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:59:00 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 02:46:07 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	zone_header_init(t_zone_header *header, t_zone *next)
{
	header->next_zone = next;
	header->prev_zone = NULL;
	if (header->next_zone)
		header->next_zone->header.prev_zone = (t_zone*)header;
	header->used_size = 0;
}

/*
**	This function create a zone of allocation of size 'zone_size' at the end of
**	the zone linked list.
**	It then adds a new entry available memory index
*/

int8_t	zone_create(t_mem_type *mem_type)
{
	t_zone			*zone;
	uint8_t			flags;

	// printf("mmap of %s zone\n", mem_type->type & HDR_TYPE_SMALL ? "small" : "tiny");

	zone = mmap(NULL, mem_type->size, PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (zone == MAP_FAILED)
	{
		dprintf(2, "Error: can't do mmap of size %lu\n", mem_type->size);
		return (ERROR);
	}

	zone_header_init(&zone->header, mem_type->zone);
	mem_type->zone = zone;

	flags = HDR_AVAILABLE | HDR_POS_LAST | HDR_POS_FIRST | mem_type->type;
	alloc_header_init(&zone->first_alloc_header,
		mem_type->size - sizeof(zone->header), 0, flags);
	available_add(&zone->first_alloc_header);
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
