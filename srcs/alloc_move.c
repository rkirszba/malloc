/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:41:43 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/23 14:42:07 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_alloc_header			*alloc_access_next(t_alloc_header *alloc)
{
	t_alloc_header		*next_alloc_header;

	if (alloc->flags & HDR_POS_LAST)
		return (NULL);
	next_alloc_header = (t_alloc_header*)((uint8_t*)alloc + alloc->size + sizeof(*alloc));
	return (next_alloc_header);
}

t_alloc_header			*alloc_access_prev(t_alloc_header *alloc)
{
	t_alloc_header		*next_alloc_header;

	if (alloc->flags & HDR_POS_FIRST)
		return (NULL);
	next_alloc_header = (t_alloc_header*)((uint8_t*)alloc - alloc->size - sizeof(*alloc));
	return (next_alloc_header);
}

t_alloc_header			*alloc_access_th(t_zone *zone, size_t umpteenth)
{
	t_alloc_header		*alloc;
	size_t		alloc_nb;

	alloc_nb = 0;
	alloc = &zone->first_alloc_header;
	while (alloc_nb < umpteenth && alloc)
	{
		alloc = alloc_access_next(alloc);
		alloc_nb++;
	}
	return (alloc);
}
