/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:59:37 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/29 14:21:49 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

#define NB_OF_SPACE		8

size_t		ft_nb_len(intmax_t n, size_t base)
{
	size_t		size;
	uintmax_t	nb;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		size++;
		nb = -n;
	}
	else
		nb = n;
	if (base == 0)
		base = 10;
	while (nb != 0)
	{
		nb /= base;
		size++;
	}
	return (size);
}

void	padding_before(t_rbt *node, size_t space)
{
	t_rbt		*parent;
	size_t		i;

	i = 0;
	parent = tree_parent(node);
	while (i < space)
	{
		printf(" ");
		i++;
	}
	if (parent != NULL)
		(parent->left == node) ? printf("╰─ ") : printf("╭─ ");
}

void	padding_after(t_rbt *node)
{
	size_t		i;
	size_t		padding;

	if (node->left != NULL || node->right != NULL)
	{
		padding = NB_OF_SPACE - 5 - 3;//'0x7f2268500298 '= 15
		i = 0;
		while (i < padding)
		{
			printf("─");
			i++;
		}
		if (tree_root(node) == node)
			printf("───");
		printf("┤");
	}
	printf("\n");
}

void	tree_print_node_color(t_rbt *node)
{
	if (node == NULL)
		printf("\033[33m");
	else if (node->color == RED)
		printf("\033[31m");
	else
		printf("\033[33m");
}

void	tree_print_node(t_rbt *node)
{
	if (!node)
	{
		printf("VOID NODE\n");
		return ;
		}
	tree_print_node_color(node->parent);
	printf("%*sParent: %p\n", 10 + 8, "", node->parent);
	if (node->parent)
		printf("%*s  Val:  %zu\n", 10 + 8, "", (size_t)node->parent->content);
	tree_print_node_color(node);
	printf("%*sSelf:   %p\n", 10 + 8, "", node);
	printf("%*s  Val:  %zu\n", 10 + 8, "", (size_t)node->content);
	tree_print_node_color(node->left);
	printf("Left:   %p", node->left);
	tree_print_node_color(node->right);
	printf("%*sRight:  %p\n", 10 + 8, "", node->right);
	tree_print_node_color(node->left);
	if (node->left)
		printf("  Val:  %-10zu", (size_t)node->left->content);
	else
		printf("        %10s", "");
	tree_print_node_color(node->right);
	if (node->right)
		printf("%*s  Val:  %-10zu", 10 + 10, "", (size_t)node->right->content);
	printf("\n\033[00m");
}

void	tree_print_elem(t_rbt *node)
{
	void	*content;

	content = (node->content);
	if (node->color == RED)
		printf("\033[31m");
	else
		printf("\033[34m");
	// printf("%p \033[00m", content);
	printf("%-4zu \033[00m", ((size_t)content));
}

void	tree_print(t_rbt *node, size_t deep)
{
	if (node == NULL)
	{
		return ;
	}
	tree_print(node->right, deep + 1);
	padding_before(node, (deep * NB_OF_SPACE));
	tree_print_elem(node);
	padding_after(node);
	tree_print(node->left, deep + 1);
}
