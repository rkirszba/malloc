/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:01:26 by arobion           #+#    #+#             */
/*   Updated: 2020/11/02 20:16:11 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE_TAB	50
#define NB_TEST		1000000
#define SIZE_ALLOC	16

int		size_tab[SIZE_TAB];

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
		((char*)mem)[i++] = (uint8_t)size;
}

void		test_read2(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		if (((uint8_t*)mem)[i++] != (uint8_t)size)
			write(1, "ERROR USER MEMORY HAS BEEN ALTERED\n", 35);
}

# define IN_START		999999999

int8_t		unit_test(t_alloc_header **tab, int index)
{
	int			r;

	r = rand() % SIZE_TAB;
	(void)index;
	test_read2(tab[r], secure_align_size(size_tab[r]));
	our_free(tab[r]);
	size_tab[r] = get_size_alloc();
	if (!(tab[r] = our_malloc(size_tab[r])))
		return (ERROR);
	test_write2(tab[r], secure_align_size(size_tab[r]));
	return (SUCCESS);
}

t_alloc_header		**init(void)
{
	t_alloc_header		**tab;
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
		size_tab[i] = SIZE_ALLOC;
		test_write2(tab[i], secure_align_size(size_tab[i]));
		i++;
	}
	return (tab);
}

void		finish(t_alloc_header **tab)
{
	int			i;
	i = 0;
	while (i < SIZE_TAB)
	{
		write(1, "o", 1);
		our_free(tab[i]);
		i++;
	}
	write(1, "e", 1);
	our_free(tab);
}

int			main(int ac, char **av)
{
	t_alloc_header		**tab;
	int			i;
	int			nb_tests = NB_TEST;

	if (ac > 1)
		nb_tests = atoi(av[1]);
	else
		nb_tests = NB_TEST;
		// srand(atoi(av[2]));
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
		if (0 == i % 1000)
			printf("%d\n", i);
		if (ERROR == unit_test(tab, i))
			return (10);
		// if (i % 100000 == 0)
		// {
		// 	print_malloc_mem();
		// 	show_alloc_mem();
		// }
	}
	write(1, "\n", 1);
	finish(tab);

	write(1, "\nEnd tests\n", 11);
	return (0);
}
