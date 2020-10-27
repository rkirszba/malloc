/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:46 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/27 18:08:26 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_av_tab(t_rbt **tab)
{
	size_t	i;

	i = 0;
	while (i <= TINY_SIZE_MAX_FACTOR)
	{
		if (tab[i])
		{
			printf("Tab[%lu]: %p\n", i, tab[i]);
			tree_print(tab[i], 4);
			tree_inorder(tab[i], print_alloc_wrapper);
		}
		i++;
	}
}

int		print_alloc_wrapper(t_rbt *rbt)
{
	print_alloc((t_alloc_header*)rbt);
	return (0);
}

void	print_debug_tree(char *s, t_rbt *tree, int8_t allocs)
{
	printf("\t%s\n", s);
	if (tree)
		tree_print(tree, 4);
	if (allocs)
		tree_inorder(tree, print_alloc_wrapper);
}

void	print_debug(size_t size)
{
	(void)size;
	return ;
	size = align_size(HDR_TYPE_TINY, size);
	printf("\n\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("available tree---------------------------------------------\n");
	print_av_tab(static_mem()->tiny.available);
	// print_debug_tree("Max size", static_mem()->tiny.available[TINY_SIZE_MAX_FACTOR], TRUE);
	// print_debug_tree("Current size", static_mem()->tiny.available[(size / RES_TINY) - 1], TRUE);
	printf("unavailable tree--------------------------------------------\n");
	print_debug_tree("", static_mem()->unavailable[0], TRUE);
}


int		main(int ac, char **av)
{
	int		size;
	void	*mem[3];

	if (ac != 2)
		return (0);
	size = atoi(av[1]);
	mem[0] = our_malloc(size);
	printf("\n\nAFTER MALLOC 0\n\n");
	print_debug(size);
	mem[1] = our_malloc(size);
	printf("\n\nAFTER MALLOC 1\n\n");

	print_debug(size);
	mem[2] = our_malloc(size);
	printf("\n\nAFTER MALLOC 2\n\n");
	print_debug(size);

	our_free(mem[1]);
	printf("\n\nAFTER FREE 1\n\n");

	print_debug(size);
	mem[1] = our_malloc(size);
	printf("\n\nAFTER MALLOC 1\n\n");
	our_free(mem[0]);
	printf("\n\nAFTER FREE 0\n\n");
	print_debug(size);
	our_free(mem[2]);
	printf("\n\nAFTER FREE 2\n\n");
	print_debug(size);
}
