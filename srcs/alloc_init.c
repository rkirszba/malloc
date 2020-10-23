/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:42:30 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/23 15:29:32 by ldevelle         ###   ########.fr       */
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
	header->size = size - sizeof(*header);
	header->size_prev = size_prev;
	header->flags = flags;
	alloc_update_size_next(header);
}
