/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_new_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:33:57 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:33:58 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_rbt		*tree_new_node(void *content, t_rbt *new_node)
{
	t_rbt		*node;

	node = new_node;
	node->content = content;
	node->color = RED;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
