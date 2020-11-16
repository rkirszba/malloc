/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex_zone.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:31:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/16 14:07:40 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void			print_zone_header(t_zone *zone, size_t *total_octet)
{
	size_t				octet;

	octet = 0;
	while (octet < sizeof(zone->header))
	{
		if (0 == *total_octet % PRINT_LINE_SIZE)
		{
			putstr("\x1b[0m");
			print_hex((size_t)(uint8_t*)zone + octet);
			putstr(": ");
		}
		mem_put_color(NULL, octet, TRUE);
		print_hex_octet(*((uint8_t*)&zone->header + octet));
		octet++;
		(*total_octet)++;
		if (0 == *total_octet % PRINT_LINE_SIZE)
			putstr("\x1b[0m\n");
	}
}

void			print_zone(t_zone *zone, size_t zone_size)
{
	t_alloc_header		*alloc;
	size_t				alloc_nb;
	size_t				total_octet;

	if (!(total_octet = 0) && PRINT_HEADER_ZONE)
		print_zone_header(zone, &total_octet);
	alloc_nb = 0;
	alloc = &zone->first_alloc_header;
	while (alloc)
	{
		if (mem_put_color(alloc, alloc_nb, FALSE) && total_octet >= zone_size)
			break ;
		if (PRINT_HEADER_ALLOC)
		{
			print_alloc_header(alloc, &total_octet);
			mem_put_color(alloc, alloc_nb, FALSE);
			if (total_octet >= zone_size)
				break ;
		}
		print_alloc_memory(alloc, &total_octet, alloc_nb);
		alloc = alloc_access_th(zone, ++alloc_nb);
	}
	putstr("\x1b[0m");
	print_hex((size_t)(uint8_t*)zone + total_octet);
	putstr("\n");
}

void			print_zone_type(t_zone *zone)
{
	size_t				zone_nb;

	zone_nb = 0;
	while (zone)
	{
		putstr("\x1b[38;2;155;155;255m");
		putstr("Printing malloc zone ");
		print_dec(zone_nb);
		putstr("\n");
		print_zone(zone, zone->header.size);
		putstr("\n");
		zone = zone->header.next_zone;
		zone_nb++;
	}
}
