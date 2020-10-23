/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 12:35:41 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/23 19:04:25 by rkirszba         ###   ########.fr       */
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
            return root;
	}
    return NULL;
	
}

t_rbt	*tree_get_recurse_func_ll(t_rbt *root, void *content, t_rbt_compare_long_long *func)
{
	if (root != NULL)
	{
		if (func(root->content, content) > 0)
			return (tree_get_recurse_func_ll(root->left, content, func));
		else if (func(root->content, content) < 0)
			return (tree_get_recurse_func_ll(root->right, content, func));
        else
            return root;
	}
    return NULL;
	
}
