/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_zone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:01:57 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/23 16:48:47 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void 			mem_put_color(t_alloc_header *alloc, int32_t alloc_nb, int8_t header)
{
	if (header == TRUE)
	{
		if (alloc_nb < 0)
		{
			alloc_nb = -(alloc_nb + 1);
			if (alloc_nb < (int)sizeof(t_rbt))
			{
				alloc_nb /= 8;
				if (alloc_nb % 2)
					printf("\x1b[38;2;%d;%d;%dm", 255, 105, 55);
				else
					printf("\x1b[38;2;%d;%d;%dm", 255, 155, 55);
			}
			else
			{
				alloc_nb /= 2;
				if (alloc_nb % 2)
					printf("\x1b[38;2;%d;%d;%dm", 255, 255, 155);
				else
					printf("\x1b[38;2;%d;%d;%dm", 255, 255, 5);
			}
		}
		else
		{
			alloc_nb /= 4;
			if (alloc_nb % 2)
				printf("\x1b[38;2;%d;%d;%dm", 55, 205, 255);
			else
				printf("\x1b[38;2;%d;%d;%dm", 5, 255, 255);
		}

	}
	else if (alloc->flags & HDR_AVAILABLE)
	{
		if (alloc_nb % 2)
			printf("\x1b[38;2;%d;%d;%dm", 155, 255, 155);
		else
			printf("\x1b[38;2;%d;%d;%dm", 105, 255, 105);
	}
	else
	{
		printf("\x1b[38;2;%d;%d;%dm", 255, 155, 155);
	}
}

void			print_alloc_header(t_alloc_header *alloc, size_t *total_octet)
{
	size_t		octet;

	octet = 0;
	while (octet < sizeof(*alloc))
	{
		if (0 == *total_octet % PRINT_LINE_SIZE)
		{
			printf("\x1b[0m");
			printf("%p: ", (uint8_t*)alloc + octet);
		}
		mem_put_color(alloc, -octet -1, TRUE);
		printf("%02hhx ", *((uint8_t*)alloc + octet));
		octet++;
		(*total_octet)++;
		if (0 == *total_octet % PRINT_LINE_SIZE)
			printf("\n");
	}
}

void			print_alloc_memory(t_alloc_header *alloc, size_t *total_octet,
				size_t alloc_nb)
{
	size_t		octet;

	octet = 0;
	while (octet < (size_t)ABS(alloc->size))
	{
		if (0 == *total_octet % PRINT_LINE_SIZE)
		{
			printf("\x1b[0m");
			printf("%p: ", (uint8_t*)alloc + sizeof(*alloc) + octet);
			mem_put_color(alloc, alloc_nb, FALSE);
		}
		printf("%02hhx ", *((uint8_t*)alloc + sizeof(*alloc) + octet));
		octet++;
		(*total_octet)++;
		if (0 == *total_octet % PRINT_LINE_SIZE)
			printf("\n");
	}
}


void			print_zone_header(t_zone *zone, size_t *total_octet)
{
	size_t		octet;

	octet = 0;
	while (octet < sizeof(zone->header))
	{
		if (0 == *total_octet % PRINT_LINE_SIZE)
		{
			printf("\x1b[0m");
			printf("%p: ", (uint8_t*)zone + octet);
		}
		mem_put_color(NULL, octet, TRUE);
		printf("%02hhx ", *((uint8_t*)&zone->header + octet));
		octet++;
		(*total_octet)++;
		if (0 == *total_octet % PRINT_LINE_SIZE)
			printf("\n");
	}
}

void			print_zone(t_zone *zone, size_t zone_size)
{
	t_alloc_header		*alloc;
	size_t		alloc_nb;
	size_t		total_octet;

	total_octet = 0;
	if (TRUE)
	{
		print_zone_header(zone, &total_octet);
		// printf("\n%*s", (int)(13 + (total_octet * 3)), " ");
	}
	alloc_nb = 0;
	alloc = &zone->first_alloc_header;
	while (alloc)
	{
		if (total_octet >= zone_size)
			break;
		mem_put_color(alloc, alloc_nb, FALSE);
		if (TRUE)
		{
			print_alloc_header(alloc, &total_octet);
			// printf("\x1b[0m");
			mem_put_color(alloc, alloc_nb, FALSE);
			if (total_octet >= zone_size)
				break;
		}
		print_alloc_memory(alloc, &total_octet, alloc_nb);
		alloc = alloc_access_th(zone, ++alloc_nb);

	}
	printf("\x1b[0m");
	printf("%p: ", (uint8_t*)zone + total_octet);
	printf("\n");
}

void		print_malloc_mem(void)
{
	t_infos			*base;
	t_zone			*zone;
	size_t			zone_nb;

	base = static_mem();
	zone = base->tiny.zone;
	zone_nb = 0;
	while (zone)
	{
		printf("\x1b[38;2;%d;%d;%dm", 155, 155, 255);
		printf("Printing malloc zone %lu:\n", zone_nb);
		print_zone(zone, base->tiny.size);
		printf("\n");
		zone = zone->header.next_zone;
		zone_nb++;
	}
}
