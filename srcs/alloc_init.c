/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:42:30 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/27 14:47:51 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	alloc_update_size_next(t_alloc_header *alloc)
{
	t_alloc_header		*next_alloc;

	next_alloc = alloc_access_next(alloc);
	if (next_alloc)
		next_alloc->size_prev = alloc->size;
}

void	alloc_header_init(t_alloc_header *header, size_t size, size_t size_prev,
		uint8_t flags)
{
	header->size = size;
	header->size_prev = size_prev;
	header->flags = flags;
	alloc_update_size_next(header);
}

void			print_alloc(t_alloc_header *alloc)
{
	uint8_t		flag;

	if (!alloc)
	{
		printf("Alloc: %p\n", alloc);
		return ;
	}
	printf("Alloc: %p\n", alloc);
	printf("\tsize     : %d\n", alloc->size);
	printf("\tsize_prev: %d\n", alloc->size_prev);
	printf("\tavail    : %d\n", alloc->flags & HDR_AVAILABLE ? TRUE : FALSE);
	flag = alloc->flags & HDR_TYPE;
	if (flag == HDR_TYPE_TINY)
		printf("\ttype     : %s\n", "Tiny");
	else if (flag == HDR_TYPE_SMALL)
		printf("\ttype     : %s\n", "Small");
	else if (flag == HDR_TYPE_LARGE)
		printf("\ttype     : %s\n", "Large");
	else
		printf("\ttype     : %s\n", "???");
	flag = alloc->flags & HDR_POS;
	printf("\tfirst    : %d\n", flag & HDR_POS_FIRST ? TRUE : FALSE);
	printf("\tlast     : %d\n", flag & HDR_POS_LAST ? TRUE : FALSE);
	printf("\n");
}
