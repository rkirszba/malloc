/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:59:00 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/27 11:03:29 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	zone_header_init(t_zone_header *header, t_zone *next, size_t size)
{
	header->next_zone = next;
	header->prev_zone = NULL;
	if (header->next_zone)
		header->next_zone->header.prev_zone = (t_zone*)header;
	header->size = size;
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

	zone_header_init(&zone->header, mem_type->zone, mem_type->size);
	mem_type->zone = zone;

	flags = HDR_AVAILABLE | HDR_POS_LAST | HDR_POS_FIRST | mem_type->type;
	alloc_header_init(&zone->first_alloc_header,
		mem_type->size - sizeof(zone->header) - sizeof(t_alloc_header), 0, flags);
	available_add(&zone->first_alloc_header);
	return (SUCCESS);
}

/*
**	Size must have been aligned with secure_align_size() before
*/

t_alloc_header	*zone_create_large(size_t size)
{
	t_zone			*zone;
	uint8_t			flags;

	// printf("mmap of %s zone\n", "large");
	zone = mmap(NULL, size + sizeof(t_zone_header) + sizeof(t_alloc_header),
				PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (zone == MAP_FAILED)
	{
		dprintf(2, "Error: can't do mmap of large size %lu\n", size);
		return (NULL);
	}

	zone_header_init(&zone->header, static_mem()->large, size);
	static_mem()->large = zone;

	flags = HDR_AVAILABLE | HDR_POS_LAST | HDR_POS_FIRST | HDR_TYPE_LARGE;
	alloc_header_init(&zone->first_alloc_header,
		size - sizeof(zone->header) - sizeof(t_alloc_header), 0, flags);
	return (&zone->first_alloc_header);
}

uint8_t		can_zone_liberate(t_alloc_header *alloc)
{
	uint8_t			retval;

	retval = FALSE;
	if (alloc->flags & HDR_AVAILABLE)
		if (alloc->flags & HDR_POS_FIRST && alloc->flags & HDR_POS_LAST)
			retval = TRUE;
	return (retval);
}

int8_t		zone_liberate(t_zone *zone)
{
	int8_t			retval;

	retval = SUCCESS;

	if (zone->header.next_zone)
		// if (zone->header.next_zone->header.prev_zone)
			zone->header.next_zone->header.prev_zone = zone->header.prev_zone;
	if (zone->header.prev_zone)
	{
		// if (zone->header.prev_zone->header.next_zone)
			zone->header.prev_zone->header.next_zone = zone->header.next_zone;
	}
	else
	{
		if (zone == static_mem()->tiny.zone)
			static_mem()->tiny.zone = zone->header.next_zone;
		else if (zone == static_mem()->small.zone)
			static_mem()->small.zone = zone->header.next_zone;
		else if (zone == static_mem()->large)
			static_mem()->large = zone->header.next_zone;
	}
	if (-1 == munmap((void*)zone, zone->header.size))
		retval = ERROR;
		//if error, should we put zone back in list ?
	return (retval);
}


int8_t	zone_liberate_all(t_zone *zone)
{
	t_zone			*n_zone;
	int8_t			retval;

	retval = SUCCESS;
	while (zone)
	{
		n_zone = zone;
		zone = zone->header.next_zone;
	    if (-1 == munmap((void*)n_zone, n_zone->header.size))
			retval = ERROR;
	}
	return (retval);
}
