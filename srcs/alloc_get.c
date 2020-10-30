/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:20:29 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/30 17:18:52 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

uint8_t				is_large_zone(size_t size)
{
	if (size > static_mem()->small.alloc_size_max)
		return (TRUE);
	return (FALSE);
}

t_alloc_header		*alloc_get_available(size_t size)
{
	t_rbt   		**tree;
	t_rbt			*node;
	int				umpteenth_node;

	if (NULL == (tree = available_get_tree_with_memory(size)))
		return (NULL);
	umpteenth_node = 0;
	if (!(node = tree_get_node_th(*tree, &umpteenth_node)))
	{
		dprintf(2, "Error: can't get %dth node of tree\n", umpteenth_node);
		return (NULL);
	}
	return ((t_alloc_header*)node);
}

//110111011110100000011111011100011100010100101100111100000000
//             10101010101010101010101010101010111001111101010
//                                       11100000

t_alloc_header		*alloc_get(size_t size)
{
	t_alloc_header	*alloc;

	// printf("size: %lu\n", size);
	size = secure_align_size(size);
	// printf("saze: %lu\n", size);
	if (TRUE == is_large_zone(size))
	{
		alloc = zone_create_large(size);
		if (NULL == alloc)
			return (NULL);
	}
	else
	{
		alloc = alloc_get_available(size);
		// printf("salo: %d\n", alloc->size);
		if (NULL == alloc)
			return (NULL);
		available_remove(alloc);
		if (SUCCESS == alloc_split_malloc(alloc, size))
		{
			// printf("---Splitted %u\n", alloc_access_next(alloc)->size);
			available_add(alloc_access_next(alloc));
		}
		// printf("spli: %d\n", alloc->size);
	}
	alloc_set_unavailable(alloc);
	unavailable_add(alloc);
	// printf("send: %d\n", alloc->size);
	return (alloc);
}
