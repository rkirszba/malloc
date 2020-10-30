/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_available.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:00:00 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/30 11:29:09 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_rbt		**available_get_tree_with_memory(size_t size_to_find)
{
	t_mem_type		*mem_type;
	size_t			index;

	mem_type = mem_type_get_from_size(size_to_find);
	// printf("Size asked: %lu\n", size_to_find);
	// if (mem_type->type & HDR_TYPE_TINY)
	// 	printf("Mem_type = %s\n", "Tiny");
	// else if (mem_type->type & HDR_TYPE_SMALL)
	// 	printf("Mem_type = %s\n", "Small");
	// else
	// 	printf("Mem_type = %s\n", "Large");
	index = (size_to_find / mem_type->alloc_resolution_size) - 1;
	if (index > mem_type->factor_size_max)
		index = mem_type->factor_size_max;

	while (index < mem_type->factor_size_max)
	{
		if (mem_type->available[index] != NULL)
		{
			// printf("1%s with index = %lu\n", __func__, index);
			return &mem_type->available[index];
		}
		index++;
	}
	if (mem_type->available[index] == NULL)
	{
		if (ERROR == zone_create(mem_type))
			return (NULL);
	}
	// printf("2%s with index = %lu\n", __func__, index);
	return (&mem_type->available[index]);
}

t_rbt		**available_get_tree(t_alloc_header *alloc)
{
	t_mem_type		*mem_type;
	size_t			index;

	mem_type = mem_type_get(alloc->flags & HDR_TYPE);
	index = (alloc->size / mem_type->alloc_resolution_size) - 1;
	if (index > mem_type->factor_size_max)
		index = mem_type->factor_size_max;
	// printf("1%s with index = %lu\n", __func__, index);
	return &mem_type->available[index];
}

void		available_add(t_alloc_header *alloc)
{
    t_rbt   **tree;

    tree = available_get_tree(alloc);
	alloc->rbt.content = alloc;
    *tree = tree_insert_func_ll(*tree, &alloc->rbt,
		(void*)alloc, &compare_adresses);
}

int8_t		available_remove(t_alloc_header *alloc)
{
    t_rbt   **tree;
    t_rbt	*node;

	tree = available_get_tree(alloc);
	if (!(node = tree_get_recurse_func_ll(*tree, alloc,
			&compare_adresses)))
	{
		dprintf(2, "Error: can't find %p in available tree\n", alloc);
		return (FAILURE);
	}
    *tree = tree_delete_node(node);
    return (SUCCESS);
}
