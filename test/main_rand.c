/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:01:26 by arobion           #+#    #+#             */
/*   Updated: 2020/10/30 15:15:27 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE_TAB	5
#define NB_TEST		1000000
#define SIZE_ALLOC	16

int		print_alloc_wrapper(t_rbt *rbt)
{
		print_alloc((t_alloc_header*)rbt);
	return (1);
}

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

void	print_debug_tree(char *s, t_rbt *tree, int8_t allocs)
{
	printf("\t%s\n", s);
	if (tree)
		tree_print(tree, 0);
	if (allocs)
		tree_inorder(tree, print_alloc_wrapper);
	printf("There is %d node\n", tree_len(tree));
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

int			get_size_alloc()
{
	return (rand() % (2 << 16));
}

void		test_write2(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((char*)mem)[i++] = 0x42;
		printf("%lu\n", i);
	}
}

int8_t		unit_test(char **tab)
{
	size_t		size;
	int			r;

	r = rand() % SIZE_TAB;

	// printf("unavailable tree--------------------------------------------\n");
	// print_debug_tree("", static_mem()->unavailable[0], FALSE);
	// printf("r = %d\n", r);
	// printf("LOOKING TO FREE %p\n", tab[r] - sizeof(t_alloc_header));
	our_free(tab[r]);
	// printf("AFTER FREE\n");
	// printf("unavailable tree--------------------------------------------\n");
	// print_debug_tree("", static_mem()->unavailable[0], FALSE);
	size = get_size_alloc();
	// printf("LOOKING TO MALLOC %zu\n", size);
	if (!(tab[r] = our_malloc(size)))
		return (ERROR);
	if (tab[r] == (void*)0x4242424242424242)
		printf("R = %d\n", r);
	// printf("AFTER NEW MALLOC\n");
	// printf("unavailable tree--------------------------------------------\n");
	// print_debug_tree("", static_mem()->unavailable[0], FALSE);
	test_write(tab[r], secure_align_size(size));
	return (SUCCESS);
}

char		**init(void)
{
	char		**tab;
	int			i;

	write(1, "v", 1);
	if (!(tab = our_malloc(sizeof(void *) * SIZE_TAB)))
		return (NULL);
	write(1, "^", 1);
	i = 0;
	write(1, "\n", 1);
	while (i < SIZE_TAB)
	{
		write(1, "x", 1);
		if (!(tab[i] = our_malloc(SIZE_ALLOC)))
			return (NULL);
		i++;
	}
	return (tab);
}

void		finish(char **tab)
{
	int			i;
	i = 0;
	while (i < SIZE_TAB)
	{
		write(1, "o", 1);
		// printf("FREE LOOKING FOR: %p\n", tab[i] - sizeof(t_alloc_header));
		// print_debug_tree("", static_mem()->unavailable[0], FALSE);
		our_free(tab[i]);
		// printf("\n\n\n\n");
		i++;
	}
	write(1, "e", 1);
	// printf("FREE LOOKING FOR: %p\n", tab - sizeof(t_alloc_header));
	// print_debug_tree("", static_mem()->unavailable[0], FALSE);
	our_free(tab);
	// printf("\n\n\n\n");
	// write(1, "o", 1);
	// print_debug_tree("", static_mem()->unavailable[0], FALSE);

}

int			main(int ac, char **av)
{
	char		**tab;
	int			i;
	int			nb_tests = NB_TEST;

	(void)ac;
	(void)av;
	(void)i;
	if (ac > 1)
		nb_tests = atoi(av[1]);
	srand(17);

	write(1, "Begin tests\n", 12);
	printf("SIZE TAB = %d\n", SIZE_TAB);
	if (!(tab = init()))
		return (10);
	write(1, "\n", 1);
	i = -1;
	// while (++i < NB_TEST)
	while (++i < nb_tests)
	{
		// write(1, "?", 1);
		if (ERROR == unit_test(tab))
			return (10);
	}
	write(1, "\n", 1);
	finish(tab);

	write(1, "\nEnd tests\n", 11);
	return (0);
}
