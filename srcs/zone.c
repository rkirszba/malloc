/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:59:00 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/23 16:51:44 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	zone_header_init(t_zone_header *header, t_zone *next)
{
	header->next_zone = next;
}

/*
**	This function create a zone of allocation of size 'zone_size' at the end of
**	the zone linked list.
**	It then adds a new entry available memory index
*/

int8_t	zone_create(t_mem_type *mem_type, uint8_t zone_type)
{
	t_zone			*zone;
	uint8_t			flags;

	zone = mmap(NULL, mem_type->size, PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (zone == MAP_FAILED)
		return (ERROR);

	zone_header_init(&zone->header, mem_type->zone);
	mem_type->zone = zone;

	flags = HDR_AVAILABLE | HDR_POS_LAST | HDR_POS_FIRST | zone_type;
	alloc_header_init(&zone->first_alloc_header,
		mem_type->size - sizeof(zone->header), 0, flags);

	return (SUCCESS);
}

void	mem_type_init(t_mem_type *mem_type, int8_t zone_type)
{
	int		page_size;

	page_size = getpagesize();//it's 4096
	if (zone_type == ZONE_TINY)
	{
		mem_type->alloc_resolution_size = page_size / 256;//it's 16
		mem_type->alloc_resolution_size = 16;
		mem_type->alloc_size_min = 0;
		mem_type->alloc_size_max = mem_type->alloc_resolution_size * 64;
		mem_type->alloc_size_max = 992;
		mem_type->size = page_size * 512;//it's 2MB = 2097152
		mem_type->size = ZONE_SIZE / 4;
	}
	else if (zone_type == ZONE_SMALL)
	{
		mem_type->alloc_size_min = 993;
		mem_type->alloc_size_max = 15360;//15kB
		mem_type->alloc_resolution_size = page_size / 8;
		mem_type->alloc_resolution_size = 512;
		mem_type->size = page_size * 4096;//16777216=16MB
		mem_type->size = mem_type->alloc_size_max * 1092;//16777216=16MB
		mem_type->size = ZONE_SIZE;
	}
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
