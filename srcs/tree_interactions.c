/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_interactions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:09:56 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/23 19:01:26 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_rbt		**get_available_tree(t_infos *infos, size_t size)
{
    /*
    ** remplacer 16 par l'element de la structure correspondante
    */
	if (size <= infos->tiny.alloc_size_max)
		return &infos->tiny.available[size / 16 - 1];
	else
		return &infos->small.available[size / 16 - 1];
	return NULL;
}

t_rbt		**get_unavailable_tree(t_infos *infos, void *ptr)
{
    size_t  hash;

    hash = hash_djb2((unsigned char*)ptr) % UNAVAILABLE_TABLE_SIZE;
    return &infos->unavailable[hash];
}

int8_t		remove_unavailable(void *alloc_header)
{
    t_infos *infos;
    t_rbt   **tree;
    t_rbt	*node;

	infos = static_mem();
	tree = get_unavailable_tree(infos, alloc_header);
	if (!(node = tree_get_recurse_func_ll(*tree, alloc_header,
			&compare_adresses)))
		return FAILURE;
    // munmap s'il s'agit d'une big zone + return SUCCESS;
    ((t_alloc_header*)alloc_header)->flags = ((t_alloc_header*)alloc_header)->flags | HDR_AVAILABLE;
    tree_delete_one_child(node);
    return SUCCESS;
}

void		add_available(t_alloc_header *alloc_header)
{
    t_infos *infos;
    t_rbt   **tree;

    infos = static_mem();
    tree = get_available_tree(infos, alloc_header->size);
    *tree = tree_insert_func_ll(*tree, &alloc_header->rbt, (void*)alloc_header, &compare_adresses);
}

long long	compare_adresses(void *content1, void *content2)
{
    return (long long)(content1 - content2);
}
