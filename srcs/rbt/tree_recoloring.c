/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_recoloring.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:33:33 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:33:34 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void		tree_recoloring(t_rbt *node)
{
	if (node->parent == NULL)
		node->color = BLACK;
	else if (node->parent->color != BLACK)
	{
		if (tree_uncle(node)->color == RED)
		{
			node->parent->color = BLACK;
			tree_uncle(node)->color = BLACK;
		}
	}
}
