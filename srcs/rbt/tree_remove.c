/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:11:36 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/27 17:59:34 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"



void		tree_replace_node(t_rbt *node, t_rbt *child)
{
	child->parent = node->parent;
	if (node->parent)
	{
		if (node == node->parent->left)
			node->parent->left = child;
		else
			node->parent->right = child;
	}
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



/*
**	This function return new root
*/

t_rbt		*tree_delete_node(t_rbt *node)
{
	t_rbt	*child;

	if (node->right == NULL)
		child = node->left;
	else
		child = node->right;
	if (child)
		tree_replace_node(node, child);
	else if (node->parent)//Has been randomly added, might be source of problems
	{
		child = node->parent;
		if (node == child->left)
			child->left = NULL;
		else
			child->right = NULL;
	}
	if (child)
	{
		if (node->color == BLACK)
		{
			if (child->color == RED)
				child->color = BLACK;
			else
				tree_delete_case_1(child);
		}
		return (tree_root(child));
	}
	return (NULL);
}

