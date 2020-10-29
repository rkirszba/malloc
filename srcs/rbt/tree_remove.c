/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 14:11:36 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/29 16:35:35 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

void		tree_cut_leaf(t_rbt *node)
{
	if (node->parent)
	{
		if (node == node->parent->left)
			node->parent->left = NULL;
		else
			node->parent->right = NULL;
	}
}


void		tree_replace_node(t_rbt *node, t_rbt *child)
{
	if (child)
		child->parent = node->parent;
	if (node->parent)
	{
		if (node == node->parent->left)
			node->parent->left = child;
		else
			node->parent->right = child;
	}
}

void		tree_copy_values(t_rbt *dest, t_rbt *src)
{
	dest->color = src->color; // peut etre qu'il ne faut pas copier la couleur
	dest->parent = src->parent;
	dest->left = src->left;
	dest->right = src->right;
	if (dest->parent)
	{
		if (src == dest->parent->left)
			dest->parent->left = dest;
		else
			dest->parent->right = dest;
	}
	if (dest->left)
		dest->left->parent = dest;
	if (dest->right)
		dest->right->parent = dest;
	// dest->content = src->content;
}

void		tree_permute_nodes(t_rbt *node1, t_rbt* node2)
{
	t_rbt	tmp1;
	t_rbt	tmp2;

	if (!node1 || !node2)
		return ;

	tree_copy_values(&tmp1, node1);
	tree_copy_values(&tmp2, node2);
	tree_copy_values(node1, &tmp2);
	tree_copy_values(node2, &tmp1);
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
	t_rbt	*in_order_pred;

	// printf("Node to delete = %zu\n", (size_t)node->content);
	if (node->right && node->left)
	{
		// printf("1\n");
		in_order_pred = tree_get_in_order_pred(node);
		// printf("In order pred = %zu\n", (size_t)in_order_pred->content);
		tree_permute_nodes(node, in_order_pred);
		// printf("Two children\nTree after permut:%zu\n", (size_t)node->content);
		// tree_print_node(node);
		// printf("\n\n");
		// tree_print_node(in_order_pred);
		// tree_print(tree_root(node), 0);
		// printf("\n\n");
		return (tree_delete_node(node));
	}
	if (node->color == RED) /*
							** normalement, il est impossible qu'un rouge ait un
							** seul enfant (pas d'enfant rouge + 0 ou 2 enfants noirs)
							*/
	{
		// printf("2\n");
		// if (node->left || node->right)
			// printf("CHILD FOR A RED NODE !!!!!!\n");
		tree_cut_leaf(node);
		return (tree_root(node->parent)); // pas genial si free
	}
	// case node is BLACK
	if (node->right == NULL)
		child = node->left;
	else
		child = node->right;
	if (child) // case the node has one child, necessarily RED
	{
		// printf("3\n");
		child->color = BLACK;
		tree_replace_node(node, child);
		return (tree_root(child));
	}
	// case node is BLACK and has no child
	// printf("HARD CASE\n");
	tree_delete_case_1(node);
	tree_cut_leaf(node);
	return (tree_root(node->parent));
}


/*
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

*/
