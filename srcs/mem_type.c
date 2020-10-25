/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:05:07 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 02:05:03 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_mem_type		*mem_type_get_from_size(size_t size)
{
	t_mem_type		*mem_type;
	t_infos	*base;

	mem_type = NULL;
	base = static_mem();
	if (size < base->tiny.alloc_size_max)
		mem_type = &base->tiny;
	else if (size < base->small.alloc_size_max)
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
	int		page_size;

	page_size = getpagesize();//it's 4096
	if (page_size <= 256)
		page_size = ZONE_SIZE;
	if (zone_type == ZONE_TINY)
	{
		mem_type->alloc_resolution_size = page_size / 256;//it's 16
		mem_type->factor_size_max = TINY__SIZE_MAX_FACTOR;
		mem_type->alloc_size_min = 0;
		mem_type->alloc_size_max = mem_type->alloc_resolution_size * TINY__SIZE_MAX_FACTOR;//normally reso * 62 which give : 992.
		//So with resolution * 64 == 1024
		mem_type->size = page_size * 512;//it's 2MB = 2097152
		mem_type->size = ZONE_SIZE / 4;
		mem_type->type = HDR_TYPE_TINY;
	}
	else if (zone_type == ZONE_SMALL)
	{
		mem_type->alloc_resolution_size = page_size / 8;
		mem_type->factor_size_max = SMALL_SIZE_MAX_FACTOR;
		mem_type->alloc_size_min = mem_type->alloc_resolution_size * 2;
		mem_type->alloc_size_max = mem_type->alloc_resolution_size * SMALL_SIZE_MAX_FACTOR;//normally * 30 wich give : 15360(15KB)
		mem_type->size = page_size * 4096;//16777216=16MB
		mem_type->size = mem_type->alloc_size_max * 1092;//16777216=16MB
		mem_type->size = ZONE_SIZE;
		mem_type->type = HDR_TYPE_SMALL;
	}
}
