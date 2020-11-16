/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zone_delete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:09:41 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:09:43 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

uint8_t			can_zone_liberate(t_alloc_header *alloc)
{
	uint8_t			retval;

	retval = FALSE;
	if (alloc->flags & HDR_AVAILABLE)
		if (alloc->flags & HDR_POS_FIRST && alloc->flags & HDR_POS_LAST)
			retval = TRUE;
	return (retval);
}

int8_t			zone_liberate(t_zone *zone)
{
	int8_t			retval;

	retval = SUCCESS;
	if (zone->header.next_zone)
		zone->header.next_zone->header.prev_zone = zone->header.prev_zone;
	if (zone->header.prev_zone)
		zone->header.prev_zone->header.next_zone = zone->header.next_zone;
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
	return (retval);
}

int8_t			zone_liberate_all(t_zone *zone)
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
