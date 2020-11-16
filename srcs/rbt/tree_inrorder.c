/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_inrorder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:34:36 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:34:36 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

int					tree_inrorder(t_rbt *root, t_rbt_inorder *func)
{
	int				value;

	value = 0;
	if (root != NULL)
	{
		value += tree_inrorder(root->right, func);
		value += func(root);
		value += tree_inrorder(root->left, func);
	}
	return (value);
}

void				*tree_inrorder_ptr(t_rbt *root, t_rbt_inorder_ptr *func)
{
	long long		value;

	value = 0;
	if (root != NULL)
	{
		value += (long long)tree_inrorder_ptr(root->right, func);
		value += (long long)func(root);
		value += (long long)tree_inrorder_ptr(root->left, func);
	}
	return ((void*)value);
}
