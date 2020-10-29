/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_trees.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:32:36 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/29 12:08:54 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

typedef struct	s_val
{
	int	value;
}				t_val;


static int	compare_values(void *val1, void *val2)
{
	return (((size_t)val1) - ((size_t)val2));
}


int main(int ac, char **av)
{
	int		i;
    int		nodes;
	//t_val	*tab_content;
	t_rbt	*tab_nodes;
	t_rbt	*tree;

	srand(0);
	(void)ac;
	nodes = atoi(av[1]);
	tab_nodes = (t_rbt*)malloc(sizeof(*tab_nodes) * nodes);
	// tab_content = (t_val*)malloc(sizeof(*tab_content) * nodes);
	i = -1;
	while (++i < nodes)
	{
		tab_nodes[i].content = (void*)(size_t)(rand() % 101);
		// tab_nodes[i].content = (void*)((size_t)tab_nodes[i].content == 62 ? (size_t)65 : (size_t)tab_nodes[i].content);
	}
	i = -1;
	tree = NULL;
	while (++i < nodes)
	{
		tree = tree_insert_func(tree, &tab_nodes[i], (void*)tab_nodes[i].content, &compare_values);
		printf("After insertion of value %zu\n\n", (size_t)tab_nodes[i].content);
		tree_print(tree, 0);
		printf("\n\n");
	}
	i = -1;
	while(++i < nodes)
	{
		tree = tree_delete_node(&tab_nodes[i]);
		printf("After deletion of value %zu\n\n", (size_t)tab_nodes[i].content);
		tree_print(tree, 0);
		printf("\n\n");
	}
	return (0);
}