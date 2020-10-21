/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:59:00 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/21 11:41:37 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

/*
**	This function create a zone of allocation of size 'zone_size' at the end of
**	the zone linked list.
**	It then adds a new entry available memory index
*/

int8_t	zone_create(t_zone **zone, size_t zone_size)
{
	while (*zone)
		*zone = (*zone)->next_zone;

	*zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (*zone == MAP_FAILED)
		return (ERROR);

	(*zone)->allocation.size = zone_size - sizeof((*zone)->allocation.size) - sizeof((*zone)->next_zone);

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
		zone = zone->next_zone;
	    if (-1 == munmap((void*)n_zone, zone_size))
			retval = ERROR;
	}
	return (retval);
}
