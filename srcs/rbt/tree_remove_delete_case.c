/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_remove_delete_case.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:43:08 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/30 13:03:19 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"
# define TREE_LEFT 1
# define TREE_RIGHT 2
# define TREE_NONE 0
# define TREE_ERROR -1

int8_t		tree_which_child(t_rbt *node)
{
	if (!node->parent)
		return (TREE_NONE);
	else if (node == node->parent->left)
		return (TREE_LEFT);
	else if (node == node->parent->right)
		return (TREE_RIGHT);
	else
		return (TREE_ERROR);
}


void        tree_delete_case_1(t_rbt *node)
{
    if (!node->parent)
        return ;
    if (!tree_sibling(node))
        tree_delete_case_1(node->parent);
    else
        tree_delete_case_2(node);
}

void        tree_delete_case_2(t_rbt *node)
{
    if (tree_sibling(node)->color == RED)
        tree_delete_case_2a(node);
    else
        tree_delete_case_2b(node);
}

void        tree_delete_case_2a(t_rbt *node)
{
    t_rbt   *parent;
    t_rbt   *sibling;

    parent = node->parent;
    sibling = tree_sibling(node);
    parent->color = RED; 
    sibling->color = BLACK;
    if (tree_which_child(sibling) == TREE_LEFT) 
        tree_rot_right(parent); 
    else
        tree_rot_left(parent); 
    tree_delete_case_1(node);
}

void        tree_delete_case_2b(t_rbt *node)
{
    t_rbt   *parent;
    t_rbt   *sibling;

    parent = node->parent;
    sibling = tree_sibling(node);
    if ((sibling->left && sibling->left->color == RED)
	|| (sibling->right && sibling->right->color == RED))
    {
        if (sibling->left != NULL && sibling->left->color == RED)
            tree_delete_case_2bi_i(node);
        else
            tree_delete_case_2bi_ii(node);
        parent->color = BLACK;
    }
    else
        tree_delete_case_2bii(node);
}

void        tree_delete_case_2bi_i(t_rbt *node)
{
    t_rbt   *parent;
    t_rbt   *sibling;

    parent = node->parent;
    sibling = tree_sibling(node);
    if (tree_which_child(sibling) == TREE_LEFT)
    { 
        sibling->left->color = sibling->color; 
        sibling->color = parent->color; 
        tree_rot_right(parent); 
    }
    else
    { 
        sibling->left->color = parent->color; 
        tree_rot_right(sibling); 
        tree_rot_left(parent); 
    }
}


void        tree_delete_case_2bi_ii(t_rbt *node)
{
    t_rbt   *parent;
    t_rbt   *sibling;

    parent = node->parent;
    sibling = tree_sibling(node);
    if (tree_which_child(sibling) == TREE_LEFT)
    { 
        sibling->right->color = parent->color; 
        tree_rot_left(sibling); 
        tree_rot_right(parent); 
    }
    else
    { 
        sibling->right->color = sibling->color; 
        sibling->color = parent->color; 
        tree_rot_left(parent); 
    }
}

void        tree_delete_case_2bii(t_rbt *node)
{
    t_rbt   *parent;
    t_rbt   *sibling;

    parent = node->parent;
    sibling = tree_sibling(node);
    sibling->color = RED; 
    if (parent->color == BLACK) 
        tree_delete_case_1(parent); 
    else
        parent->color = BLACK; 
}