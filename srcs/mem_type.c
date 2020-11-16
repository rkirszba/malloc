/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:12:21 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:12:23 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_mem_type		*mem_type_get_from_size(size_t size)
{
	t_mem_type		*mem_type;
	t_infos			*base;

	mem_type = NULL;
	base = static_mem();
	if (size <= base->tiny.alloc_size_max)
		mem_type = &base->tiny;
	else if (size <= base->small.alloc_size_max)
		mem_type = &base->small;
	return (mem_type);
}

t_mem_type		*mem_type_get(uint8_t type)
{
	t_mem_type		*mem_type;
	t_infos			*base;

	mem_type = NULL;
	base = static_mem();
	if (type == HDR_TYPE_TINY)
		mem_type = &base->tiny;
	else if (type == HDR_TYPE_SMALL)
		mem_type = &base->small;
	return (mem_type);
}

/*
**	getpagesize() == 4096
**
**	Tiny:
**		Range:	0 - 1024
**		Size:	2097152 (2MB)
**
**	Small:
**		Range:	1024 - 15360 (15KB)
**		Size:	16777216 (16MB)
*/

void			mem_type_init(t_mem_type *mem_type, int8_t zone_type)
{
	size_t		page_size;

	page_size = getpagesize();
	if (!page_size)
		page_size = 4096;
	if (zone_type == ZONE_TINY)
	{
		mem_type->type = HDR_TYPE_TINY;
		mem_type->alloc_resolution_size = RES_TINY;
		mem_type->factor_size_max = TINY_SIZE_MAX_FACTOR;
		mem_type->alloc_size_min = RES_TINY * 1;
		mem_type->alloc_size_max = RES_TINY * TINY_SIZE_MAX_FACTOR;
		mem_type->size = (SIZE_TINY - 1) + page_size
				- (SIZE_TINY - 1) % page_size;
	}
	else if (zone_type == ZONE_SMALL)
	{
		mem_type->type = HDR_TYPE_SMALL;
		mem_type->alloc_resolution_size = RES_SMALL;
		mem_type->factor_size_max = SMALL_SIZE_MAX_FACTOR;
		mem_type->alloc_size_min = RES_TINY * TINY_SIZE_MAX_FACTOR + 1;
		mem_type->alloc_size_max = RES_SMALL * SMALL_SIZE_MAX_FACTOR;
		mem_type->size = (SIZE_SMALL - 1) + page_size
				- (SIZE_SMALL - 1) % page_size;
	}
}
