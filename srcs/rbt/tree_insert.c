/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:56:28 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/22 17:13:20 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_rbt		*tree_insert_func(t_rbt *root, t_rbt *new_node, void *content,
			t_rbt_compare *func)
{
	t_rbt	*n;

	n = tree_new_node(content, new_node);
	tree_insert_recurse_func(root, n, func);
	tree_insert_repair(n);
	root = tree_root(n);
	return (root);
}
