/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_unavailable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:09:56 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/25 02:44:54 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_rbt		**unavailable_get_tree(void *ptr)
{
	t_infos *infos;
    size_t  hash;

	infos = static_mem();
    hash = hash_djb2((unsigned char*)ptr) % UNAVAILABLE_TABLE_SIZE;
    return &infos->unavailable[hash];
}

int8_t		unavailable_remove(void *maybe_alloc_header)
{
    t_rbt   **tree;
    t_rbt	*node;

	tree = unavailable_get_tree(maybe_alloc_header);
	if (!(node = tree_get_recurse_func_ll(*tree, maybe_alloc_header,
			&compare_adresses)))
		return FAILURE;
    // munmap s'il s'agit d'une big zone + return SUCCESS;
    ((t_alloc_header*)maybe_alloc_header)->flags |= HDR_AVAILABLE;
	*tree = tree_delete_node(node);
    return SUCCESS;
}

void		unavailable_add(t_alloc_header *alloc_header)
{
    t_rbt   **tree;

    tree = unavailable_get_tree(alloc_header);
    *tree = tree_insert_func_ll(*tree, &alloc_header->rbt,
		(void*)alloc_header, &compare_adresses);
}


long long	compare_adresses(void *content1, void *content2)
{
    return (long long)(content1 - content2);
}
