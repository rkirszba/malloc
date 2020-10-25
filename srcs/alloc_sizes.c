/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_sizes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:34:40 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 16:30:50 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

size_t			align_size(uint8_t type_flag, size_t size)
{
	if (type_flag & HDR_TYPE_TINY)
		size = (((size - 1) >> 4) << 4) + 16;
	if (type_flag & HDR_TYPE_SMALL)
		size = (((size - 1) >> 9) << 9) + 512;
	if (type_flag & HDR_TYPE_LARGE)
		size = (((size - 1) >> 12) << 12) + 4096;
	return (size);
}

size_t			secure_align_size(size_t size)
{
	t_infos			*base;
	size_t			aligned_size;

	base = static_mem();
	aligned_size = align_size(HDR_TYPE_TINY, size);
	if (aligned_size < base->tiny.alloc_size_max)
		return (aligned_size);
	aligned_size = align_size(HDR_TYPE_SMALL, size);
	if (aligned_size <= base->small.alloc_size_max)
		return (aligned_size);
	//as secure align should be used when receiving size in malloc
	//if large zone is needed, it directly gives the right size for zone_create
	aligned_size = align_size(HDR_TYPE_LARGE,
		size + sizeof(t_zone_header) + sizeof(t_alloc_header));
	return (aligned_size);
}
