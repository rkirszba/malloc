/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:34:49 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:34:50 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_rbt	*tree_get_recurse_func(t_rbt *root, void *content, t_rbt_compare *func)
{
	if (root != NULL)
	{
		if (func(root->content, content) > 0)
			return (tree_get_recurse_func(root->left, content, func));
		else if (func(root->content, content) < 0)
			return (tree_get_recurse_func(root->right, content, func));
		else
			return (root);
	}
	return (NULL);
}

t_rbt	*tree_get_recurse_func_ll(t_rbt *root, void *content,
		t_rbt_compare_long_long *func)
{
	if (root != NULL)
	{
		if (func(root->content, content) > 0)
			return (tree_get_recurse_func_ll(root->left, content, func));
		else if (func(root->content, content) < 0)
			return (tree_get_recurse_func_ll(root->right, content, func));
		else
			return (root);
	}
	return (NULL);
}

t_rbt	*tree_get_node_th(t_rbt *root, int *umpteenth)
{
	t_rbt			*node;

	node = NULL;
	if (NULL != root)
	{
		node = tree_get_node_th(root->left, umpteenth);
		if (!*umpteenth || NULL != node)
			return (root);
		(*umpteenth)--;
		node = tree_get_node_th(root->right, umpteenth);
	}
	return (node);
}

t_rbt	*tree_get_in_order_pred(t_rbt *node)
{
	t_rbt *in_order_pred;

	if (!node)
		return (NULL);
	in_order_pred = node->left;
	while (in_order_pred && in_order_pred->right)
	{
		in_order_pred = in_order_pred->right;
	}
	return (in_order_pred);
}
