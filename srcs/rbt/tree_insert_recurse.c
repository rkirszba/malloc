/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_insert_recurse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:34:15 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:34:16 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void		tree_insert_recurse_func(t_rbt *root, t_rbt *n, t_rbt_compare *func)
{
	if (root != NULL)
	{
		if (func(root->content, n->content) > 0)
			if (root->left != NULL)
			{
				tree_insert_recurse_func(root->left, n, func);
				return ;
			}
			else
				root->left = n;
		else
		{
			if (root->right != NULL)
			{
				tree_insert_recurse_func(root->right, n, func);
				return ;
			}
			else
				root->right = n;
		}
	}
	n->parent = root;
	n->left = NULL;
	n->right = NULL;
	n->color = RED;
}

void		tree_insert_recurse_func_ll(t_rbt *root, t_rbt *n,
				t_rbt_compare_long_long *func)
{
	if (root != NULL)
	{
		if (func(root->content, n->content) > 0)
			if (root->left != NULL)
			{
				tree_insert_recurse_func_ll(root->left, n, func);
				return ;
			}
			else
				root->left = n;
		else
		{
			if (root->right != NULL)
			{
				tree_insert_recurse_func_ll(root->right, n, func);
				return ;
			}
			else
				root->right = n;
		}
	}
	n->parent = root;
	n->left = NULL;
	n->right = NULL;
	n->color = RED;
}
