/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:11:36 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/23 14:05:06 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void		tree_replace_node(t_rbt *node, t_rbt *child)
{
	child->parent = node->parent;
	if (node == node->parent->left)
		node->parent->left = child;
	else
		node->parent->right = child;
}

void		tree_delete_one_child(t_rbt *node)
{
	t_rbt	*child;

	if (node->right == NULL)
		child = node->left;
	else
		child = node->right;
	if (child)
	{
		tree_replace_node(node, child);
		if (node->color == BLACK)
		{
			if (child->color == RED)
				child->color = BLACK;
			else
				tree_delete_case_1(child);
		}
	}
	// return (node);
	// if (func)
	// 	func(&node->content);
	// ft_memdel((void**)&node);
}
