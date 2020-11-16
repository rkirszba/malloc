/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_genealogy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:34:55 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:34:55 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_rbt		*tree_parent(t_rbt *node)
{
	if (node)
		return (node->parent);
	return (NULL);
}

t_rbt		*tree_grand_parent(t_rbt *node)
{
	return (tree_parent(tree_parent(node)));
}

t_rbt		*tree_root(t_rbt *node)
{
	t_rbt	*up;

	up = tree_parent(node);
	while (up != NULL)
	{
		node = up;
		up = tree_parent(node);
	}
	return (node);
}

t_rbt		*tree_sibling(t_rbt *node)
{
	if (node && node->parent)
	{
		if (node == node->parent->left)
		{
			return (node->parent->right);
		}
		else if (node == node->parent->right)
		{
			return (node->parent->left);
		}
	}
	return (NULL);
}

t_rbt		*tree_uncle(t_rbt *node)
{
	return ((tree_sibling(tree_parent(node))));
}
