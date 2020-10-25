/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_available.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 00:00:00 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 02:54:04 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_rbt		**available_get_tree_with_memory(size_t size_to_find)
{
	t_mem_type		*mem_type;
	size_t			index;

	mem_type = mem_type_get_from_size(size_to_find);
	index = (size_to_find / mem_type->alloc_resolution_size) - 1;
	if (index > mem_type->factor_size_max)
		index = mem_type->factor_size_max;

	printf("***ATWM search starting at index is %lu\n", index);
	while (index < mem_type->factor_size_max)
	{
		if (mem_type->available[index] != NULL)
		{
			printf("***ATWM search success in while at index is %lu\n", index);
			return &mem_type->available[index];
		}
		index++;
	}
	if (mem_type->available[index] == NULL)
	{
		printf("***ATWM no available alloc of Ronflex size, need to mmap\n");
		if (ERROR == zone_create(mem_type))
			return (NULL);
	}
	printf("***ATWM search success at end index is %lu\n", index);
	return (&mem_type->available[index]);
}

//	Carefull, should not return tree from size, because ending alloc rarely has
//	size which 'belong' to tree of his mem type
t_rbt		**available_get_tree(size_t size, uint8_t type)
{
	t_mem_type		*mem_type;
	size_t			index;

	printf("***Asking a tree for size %lu\n", size);
	mem_type = mem_type_get(type);
	index = (size / mem_type->alloc_resolution_size) - 1;
	if (index > mem_type->factor_size_max)
		index = mem_type->factor_size_max;
	printf("***AT Index is %lu\n", index);
	return &mem_type->available[index];
}

void		available_add(t_alloc_header *alloc)
{
    t_rbt   **tree;

	printf("***available add request of alloc_header %p\n", alloc);
    tree = available_get_tree(alloc->size, alloc->flags & HDR_TYPE);
	printf("***available will add to tree %p\n", *tree);
	alloc->rbt.content = alloc;
    *tree = tree_insert_func_ll(*tree, &alloc->rbt,
		(void*)alloc, &compare_adresses);
	printf("***available has added tot tree %p\n", *tree);
}

int8_t		available_remove(t_alloc_header *alloc)
{
    t_rbt   **tree;
    t_rbt	*node;

	printf("***available remove request of alloc_header %p, size %d\n", alloc, alloc->size);
	tree = available_get_tree(alloc->size, alloc->flags & HDR_TYPE);
	printf("***available will remove from tree %p\n", *tree);
	if (!(node = tree_get_recurse_func_ll(*tree, alloc,
			&compare_adresses)))
	{
		dprintf(2, "Error: can't find %p in available tree\n", alloc);
		return (FAILURE);
	}
    *tree = tree_delete_node(node);
    return (SUCCESS);
}
