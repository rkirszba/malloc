/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 18:51:38 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/22 17:19:38 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <limits.h>
# include <stdlib.h>
# include <inttypes.h>
# include <stdio.h>

enum	e_color {BLACK, RED};

typedef struct		s_rbt
{
	struct s_rbt	*parent;
	struct s_rbt	*left;
	struct s_rbt	*right;
	void			*content;
	enum e_color	color;
}					t_rbt;

typedef	int				(t_rbt_compare)				(void *, void *);
typedef	int				(t_rbt_inorder)				(t_rbt *);
typedef	void			*(t_rbt_inorder_ptr)		(t_rbt *);
typedef	void			(t_rbt_free_content)		(void **);


size_t	ft_nb_len(intmax_t n, size_t base);
void	padding_after(t_rbt *node);
void	padding_before(t_rbt *node, size_t space);
void	tree_delete_case_1(t_rbt *node);
void	tree_delete_case_2(t_rbt *node);
void	tree_delete_case_3(t_rbt *node);
void	tree_delete_case_4(t_rbt *node);
void	tree_delete_case_5(t_rbt *node);
void	tree_delete_case_6(t_rbt *node);
void	tree_delete_one_child(t_rbt *node, t_rbt_free_content *func);
void	tree_free(t_rbt *root, t_rbt_free_content *func);
t_rbt	*tree_grand_parent(t_rbt *node);
int		tree_inorder(t_rbt *root, t_rbt_inorder *func);
void	*tree_inorder_ptr(t_rbt *root, t_rbt_inorder_ptr *func);
int		tree_inrorder(t_rbt *root, t_rbt_inorder *func);
void	*tree_inrorder_ptr(t_rbt *root, t_rbt_inorder_ptr *func);
void	tree_insert_case_1(t_rbt *n);
void	tree_insert_case_2(t_rbt *n);
void	tree_insert_case_3(t_rbt *n);
void	tree_insert_case_4(t_rbt *n);
t_rbt	*tree_insert_func(t_rbt *root, t_rbt *new_node, void *content,
		t_rbt_compare *func);
void	tree_insert_recurse_func(t_rbt *root, t_rbt *n, t_rbt_compare *func);
void	tree_insert_repair(t_rbt *n);
t_rbt	*tree_new_node(void *content, t_rbt *new_node);
t_rbt	*tree_parent(t_rbt *node);
void	tree_print(t_rbt *node, size_t deep);
void	tree_print_elem(t_rbt *node);
void	tree_recoloring(t_rbt *node);
void	tree_replace_node(t_rbt *node, t_rbt *child);
t_rbt	*tree_root(t_rbt *node);
void	tree_rot_left(t_rbt *node);
void	tree_rot_right(t_rbt *node);
t_rbt	*tree_sibling(t_rbt *node);
t_rbt	*tree_uncle(t_rbt *node);

#endif
