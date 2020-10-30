/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_tree_remove_case_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 11:37:36 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/30 12:57:05 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "tree.h"
# define TREE_LEFT 1
# define TREE_RIGHT 2
# define TREE_NONE 0
# define TREE_ERROR -1


int8_t		old_tree_which_child(t_rbt *node)
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




void		tree_del_gg(t_rbt *x)
{
    if (x->parent == NULL) 
      // Reached root 
      return; 
  
    t_rbt *sibling = tree_sibling(x);
	t_rbt *parent = x->parent; 
    if (sibling == NULL) // in theory, not possible
	{
		printf("VEEERRRRY WWEEEEEEEEIIIIIIIIRD\n");
		// No sibiling, double black pushed up 
		tree_del_gg(parent); 
    }
	else
	{ 
		if (sibling->color == RED) 
		{ 
			// Sibling red 
			parent->color = RED; 
			sibling->color = BLACK; 
			if (tree_which_child(sibling) == TREE_LEFT) 
			{ 
				// left case 
				tree_rot_right(parent); 
			} 
			else
			{ 
				// right case 
				tree_rot_left(parent); 
			} 
			tree_del_gg(x); 
		}
		else
		{ 
			// Sibling black 
			if ((sibling->left && sibling->left->color == RED)
			|| (sibling->right && sibling->right->color == RED))
			{ 
				// at least 1 red children 
				if (sibling->left != NULL && sibling->left->color == RED)
				{ 
					if (tree_which_child(sibling) == TREE_LEFT)
					{ 
						// left left 
						sibling->left->color = sibling->color; 
						sibling->color = parent->color; 
						tree_rot_right(parent); 
					}
					else
					{ 
						// right left 
						sibling->left->color = parent->color; 
						tree_rot_right(sibling); 
						tree_rot_left(parent); 
					} 
				}
				else
				{ 
					if (tree_which_child(sibling) == TREE_LEFT)
					{ 
						// left right 
						sibling->right->color = parent->color; 
						tree_rot_left(sibling); 
						tree_rot_right(parent); 
					}
					else
					{ 
						// right right 
						sibling->right->color = sibling->color; 
						sibling->color = parent->color; 
						tree_rot_left(parent); 
					} 
				} 
				parent->color = BLACK; 
			}
			else
			{ 
				// 2 black children 
				sibling->color = RED; 
				if (parent->color == BLACK) 
					tree_del_gg(parent); 
				else
					parent->color = BLACK; 
			} 
		} 
    } 
}

void		old_tree_delete_case_1(t_rbt *x)
{
	tree_del_gg(x);
}


// void		old_tree_delete_case_1(t_rbt *node)
// {
// 	if (node->parent != NULL) // 3.2 resolu = pas root 
// 	{
// 		// if (tree_sibling(node)) ==> apparently necessary
// 		tree_delete_case_2(node);
// 	}
// }


void		tree_delete_case_2_gg(t_rbt *node)
{
	t_rbt	*sibling;

	sibling = tree_sibling(node);
	if (sibling->color == BLACK)//3.2.a start
	{
		if ((sibling->left && sibling->left->color == RED)
		|| (sibling->right && sibling->right->color == RED))//3.2.a
		{
			// if (tree_which_child(sibling) == TREE_LEFT && )//3.2.a.1
			// if ()//3.2.a.2
			// if ()//3.2.a.3
			// if ()//3.2.a.4

		}
	}
	tree_delete_case_3(node);
}

void		old_tree_delete_case_2(t_rbt *node)
{
	t_rbt	*sibling;

	sibling = tree_sibling(node);
	if (sibling->color == RED)
	{
		node->parent->color = RED;
		sibling->color = BLACK;
		if (node == node->parent->left)
		{
			tree_rot_right(node->parent);
		}
		else
		{
			tree_rot_left(node->parent);
		}
	}
	tree_delete_case_3(node);
}

void		tree_delete_case_3(t_rbt *node)
{
	t_rbt	*sibling;

	sibling = tree_sibling(node);
	if ((node->parent->color == BLACK) && (sibling->color == BLACK)
	&& (sibling->left->color == BLACK) && (sibling->right->color == BLACK))
	{
		sibling->color = RED;
		tree_delete_case_1(node->parent);
	}
	else
	{
		tree_delete_case_4(node);
	}
}

void		tree_delete_case_4(t_rbt *node)
{
	t_rbt	*sibling;

	sibling = tree_sibling(node);
	if ((node->parent->color == RED) && (sibling->color == BLACK)
	&& (sibling->left->color == BLACK) && (sibling->right->color == BLACK))
	{
		sibling->color = RED;
		node->parent->color = BLACK;
	}
	else
	{
		tree_delete_case_5(node);
	}
}

void		tree_delete_case_5(t_rbt *node)
{
	t_rbt	*sibling;

	sibling = tree_sibling(node);
	if (sibling->color == BLACK)
	{
		if ((node == node->parent->left) && (sibling->right->color == BLACK)
		&& (sibling->left->color == RED))
		{
			sibling->color = RED;
			sibling->left->color = BLACK;
			tree_rot_right(sibling);
		}
		else if ((node == node->parent->right)
		&& (sibling->left->color == BLACK) && (sibling->right->color == RED))
		{
			sibling->color = RED;
			sibling->right->color = BLACK;
			tree_rot_left(sibling);
		}
	}
	tree_delete_case_6(node);
}
*/