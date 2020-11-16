/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_inorder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:34:42 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:34:42 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

int					tree_inorder(t_rbt *root, t_rbt_inorder *func)
{
	int				value;

	value = 0;
	if (root != NULL)
	{
		value += tree_inorder(root->left, func);
		value += func(root);
		value += tree_inorder(root->right, func);
	}
	return (value);
}

void				*tree_inorder_ptr(t_rbt *root, t_rbt_inorder_ptr *func)
{
	long long		value;

	value = 0;
	if (root != NULL)
	{
		value += (long long)tree_inorder_ptr(root->left, func);
		value += (long long)func(root);
		value += (long long)tree_inorder_ptr(root->right, func);
	}
	return ((void*)value);
}
