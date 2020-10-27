/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mal_fre.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:46 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/27 15:15:07 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	print_av_tab(t_rbt **tab)
{
	size_t	i;

	i = 0;
	while (i < TINY_SIZE_MAX_FACTOR)
	{
		printf("Tab[%lu]: %p\n", i, tab[i]);
		i++;
	}
}

void	print_debug(size_t size)
{
	t_rbt		*tree;

	size = align_size(HDR_TYPE_TINY, size);
	printf("\n\n");
	printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("available tree---------------------------------------------\n");
	print_av_tab(static_mem()->tiny.available);
	printf("\tMax size\n");
	tree = static_mem()->tiny.available[TINY_SIZE_MAX_FACTOR];
	if (tree)
		tree_print(tree, 4);
	printf("\tCurrent size\n");
	tree = static_mem()->tiny.available[(size / RES_TINY) - 1];
	if (tree)
		tree_print(tree, 4);
	printf("unavailable tree--------------------------------------------\n");
	tree = static_mem()->unavailable[0];
	if (tree)
		tree_print(tree, 4);
}


int		main(int ac, char **av)
{
	int		size;
	void	*mem[3];

	if (ac != 2)
		return (0);
	size = atoi(av[1]);
	mem[0] = our_malloc(size);
	print_debug(size);
	mem[1] = our_malloc(size);
	print_debug(size);

	our_free(mem[0]);
	print_debug(size);
	our_free(mem[1]);
	print_debug(size);

}
