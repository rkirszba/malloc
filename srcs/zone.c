/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:59:00 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/20 19:55:01 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

/*
**	This function create a zone of allocation of size 'zone_size' at the end of
**	the zone linked list.
**	It then adds a new entry available memory index
*/

int8_t	zone_create(t_zone_alloc **zone, size_t zone_size)
{
	while (*zone)
		*zone = (*zone)->next_zone;

	*zone = mmap(NULL, zone_size, PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (*zone == MAP_FAILED)
		return (ERROR);

	(*zone)->allocation.size = zone_size - sizeof((*zone)->allocation.size);

	//add_available_alloc((*zone), zone_size);
	return (SUCCESS);
}


int8_t	zone_all_liberate(t_zone_alloc *zone, size_t zone_size)
{
	t_zone_alloc	*n_zone;
	int8_t			retval;

	retval = SUCCESS;
	while (zone)
	{
		n_zone = zone;
		zone = zone->next_zone;
	    if (munmap((void*)n_zone, zone_size) == -1)
			retval = ERROR;
	}
	return (retval);
}
