/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_zone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:01:57 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/21 12:22:24 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void 			mem_put_color(t_alloc *alloc, int8_t alloc_nb)
{
	if (alloc->size > 0)
	{
		if (alloc_nb % 2)
			printf("\x1b[38;2;%d;%d;%dm", 155, 255, 155);
		else
			printf("\x1b[38;2;%d;%d;%dm", 205, 255, 205);
	}
	else if (alloc->size < 0)
	{
		printf("\x1b[38;2;%d;%d;%dm", 255, 155, 155);
	}
	else
	{
		printf("\x1b[38;2;%d;%d;%dm", 255, 255, 155);
	}
}

void			print_alloc(t_alloc *alloc, size_t *total_octet,
				size_t alloc_nb)
{
	size_t		octet;

	octet = 0;
	while (octet < (size_t)ABS(alloc->size))
	{
		if (0 == *total_octet % PRINT_LINE_SIZE)
		{
			printf("\x1b[0m");
			printf("%p: ", (uint8_t*)alloc + sizeof(alloc->size) + octet);
			mem_put_color(alloc, alloc_nb);
		}
		printf("%02hhd ", *((uint8_t*)alloc + sizeof(alloc->size) + octet));
		octet++;
		(*total_octet)++;
		if (0 == *total_octet % PRINT_LINE_SIZE)
			printf("\n");
	}
}

void			print_zone(t_zone *zone, size_t zone_size)
{
	t_alloc		*alloc;
	size_t		alloc_nb;
	size_t		total_octet;

	total_octet = 0;
	alloc_nb = 0;
	alloc = alloc_access_th(zone, zone_size, alloc_nb);
	while (alloc)
	{
		mem_put_color(alloc, alloc_nb);
		print_alloc(alloc, &total_octet, alloc_nb);
		alloc = alloc_access_th(zone, zone_size, ++alloc_nb);

	}
	printf("\n");
	printf("\x1b[0m");
}

void		print_malloc_mem(void)
{
	t_malloc		*base;
	t_zone			*zone;
	size_t			zone_nb;

	base = *static_mem();
	zone = base->tiny_zone;
	zone_nb = 0;
	while (zone)
	{
		printf("\x1b[38;2;%d;%d;%dm", 155, 155, 255);
		printf("Printing malloc zone %lu:\n", zone_nb);
		print_zone(zone, base->tiny_zone_size);
		zone = zone->next_zone;
		zone_nb++;
	}
}
