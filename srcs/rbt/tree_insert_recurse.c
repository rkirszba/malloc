/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_insert_recurse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:46:48 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/22 17:13:55 by ldevelle         ###   ########.fr       */
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
