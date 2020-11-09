/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:07:13 by ldevelle          #+#    #+#             */
/*   Updated: 2020/11/09 17:55:10 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void			show_alloc_alloc(void *ptr, size_t size)
{
	print_hex((size_t)ptr);
	write(1, " - ", 3);
	print_hex((size_t)ptr + size);
	write(1, " : ", 3);
	print_dec(size);
	write(1, " octets\n", 8);
}

void			show_alloc_zone(t_zone *z)
{
	t_alloc_header		*alloc;

	write(1, "\x1b[38;2;155;155;255m", 19);
	if (HDR_TYPE_LARGE == (z->first_alloc_header.flags & HDR_TYPE))
		write(1, "LARGE : ", 8);
	else if (HDR_TYPE_TINY == (z->first_alloc_header.flags & HDR_TYPE))
		write(1, "TINY : ", 7);
	else if (HDR_TYPE_SMALL == (z->first_alloc_header.flags & HDR_TYPE))
		write(1, "SMALL : ", 8);
	print_hex((size_t)z);
	write(1, "\x1b[0m\n", 5);
	alloc = &z->first_alloc_header;
	if (HDR_TYPE_LARGE == (z->first_alloc_header.flags & HDR_TYPE))
		show_alloc_alloc((void*)alloc, z->header.size - sizeof(t_zone));
	else
		while (alloc)
		{
			if (alloc->flags & HDR_AVAILABLE)
				write(1, "\x1b[38;2;155;255;155m", 19);
			else
				write(1, "\x1b[38;2;255;155;155m", 19);
			show_alloc_alloc((void*)alloc, alloc->size);
			write(1, "\x1b[0m", 4);
			alloc = alloc_access_next(alloc);
		}
}

size_t			first_biggest_than(t_zone *zone, size_t bound)
{
	size_t		smallest;

	smallest = -1;
	while (zone)
	{
		if ((size_t)zone > bound && (size_t)zone < smallest)
			smallest = (size_t)zone;
		zone = zone->header.next_zone;
	}
	return (smallest);
}

t_zone			*next_smallest(size_t smallest)
{
	size_t		tiny;
	size_t		small;
	size_t		large;
	t_zone		*winner;

	tiny = first_biggest_than(static_mem()->tiny.zone, smallest);
	small = first_biggest_than(static_mem()->small.zone, smallest);
	large = first_biggest_than(static_mem()->large, smallest);
	if (tiny < small)
	{
		if (tiny < large)
			winner = (t_zone*)tiny;
		else
			winner = (t_zone*)large;
	}
	else
	{
		if (small < large)
			winner = (t_zone*)small;
		else
			winner = (t_zone*)large;
	}
	return (winner);
}

void			show_alloc_mem(void)
{
	t_zone			*zone;
	size_t			smallest;

	smallest = 0;
	zone = next_smallest(smallest);
	if ((size_t)zone == (size_t)-1)
		write(1, "Malloc memory is empty\n: ", 23);
	while ((size_t)zone != (size_t)-1)
	{
		show_alloc_zone(zone);
		zone = next_smallest((size_t)zone);
	}
}
