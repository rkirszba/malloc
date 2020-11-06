/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:05:07 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/06 17:35:34 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_mem_type		*mem_type_get_from_size(size_t size)
{
	t_mem_type		*mem_type;
	t_infos	*base;

	mem_type = NULL;
	base = static_mem();
	if (size <= base->tiny.alloc_size_max)
		mem_type = &base->tiny;
	else if (size <= base->small.alloc_size_max)
		mem_type = &base->small;
	//carefull for large
	return mem_type;
}

t_mem_type		*mem_type_get(uint8_t type)
{
	t_infos	*base;

	base = static_mem();
	if (type == HDR_TYPE_TINY)
		return &base->tiny;
	else if (type == HDR_TYPE_SMALL)
		return &base->small;
	//carefull for large
	return NULL;
}

void	mem_type_init(t_mem_type *mem_type, int8_t zone_type)
{
	size_t		page_size;

	page_size = getpagesize();//it's 4096
	if (!page_size)
		page_size = 4096;
	/*
	while (page_size < ((RES_SMALL + sizeof(t_alloc_header)) * SMALL_SIZE_MAX_FACTOR * 100 + sizeof(t_zone_header)) / 4096)
		page_size += getpagesize();
		*/
	// ft_putnbr(page_size);
	// write(1, "\n", 1);
	if (zone_type == ZONE_TINY)
	{
		mem_type->type = HDR_TYPE_TINY;
		mem_type->alloc_resolution_size = RES_TINY;
		mem_type->factor_size_max = TINY_SIZE_MAX_FACTOR;
		mem_type->alloc_size_min = RES_TINY * 1;
		mem_type->alloc_size_max = RES_TINY * TINY_SIZE_MAX_FACTOR;//normally reso * 62 which give : 992.
		//So with resolution * 64 == 1024
		// mem_type->size = page_size * 512;//it's 2MB = 2097152
		mem_type->size = (2097152 - 1) + page_size - (2097152 - 1) % page_size; 
		// ft_putnbr(mem_type->size);
		// write(1, "\n", 1);
	}
	else if (zone_type == ZONE_SMALL)
	{
		mem_type->type = HDR_TYPE_SMALL;
		mem_type->alloc_resolution_size = RES_SMALL;
		mem_type->factor_size_max = SMALL_SIZE_MAX_FACTOR;
		mem_type->alloc_size_min = RES_TINY * TINY_SIZE_MAX_FACTOR + 1;
		mem_type->alloc_size_max = RES_SMALL * SMALL_SIZE_MAX_FACTOR;//normally * 30 wich give : 15360(15KB)
		// mem_type->size = page_size * 4096;//16777216=16MB
		mem_type->size = (16777216 - 1) + page_size - (16777216 -1 ) % page_size;
		// ft_putnbr(mem_type->size);
		// write(1, "\n", 1);
	}
}
