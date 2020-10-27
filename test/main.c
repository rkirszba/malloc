/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:46 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/26 11:23:49 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		main(int ac, char **av)
{
	int		size;
	void	*mem;
//	void	*mem_2;
//	void	*mem_large;

	if (ac != 2)
		return (0);
	size = atoi(av[1]);
	mem = our_malloc(size);
	printf("We got mem %p\n", mem);
	print_malloc_mem();
	tree_print(*unavailable_get_tree(mem), 2);
	// mem_2 = our_malloc(size);
	// printf("We got mem %p\n", mem_2);
	// print_malloc_mem();
	// tree_print(*unavailable_get_tree(mem), 2);
	our_free(mem);
	printf("We got mem %p\n", mem);
	print_malloc_mem();
	tree_print(*unavailable_get_tree(mem), 2);
	mem = our_malloc(size);
	printf("We got mem %p\n", mem);
	print_malloc_mem();
	tree_print(*unavailable_get_tree(mem), 2);

	// mem = our_malloc(size);
	// mem = our_malloc(size);
	// mem = our_malloc(size);
	// mem = our_malloc(size);
	// mem = our_malloc(size);
	// mem = our_malloc(size);
	// mem = our_malloc(size);
	// mem = our_malloc(size);
	// tree_print(*unavailable_get_tree(mem), 7);

	// printf("We got mem %p\n", mem);
	// print_malloc_mem();
	// mem_2 = our_malloc(size * 2);
	// printf("We got mem2 %p\n", mem_2);


	// mem_large = our_malloc(16777216 * 2);
	// print_malloc_mem();
	// test_write(mem, size);
	// // test_read(mem, size);

	// test_write(mem_2, size *2);
	// test_write(mem_large, 16777216 * 2);
	// printf("Print test write\n");
	// print_malloc_mem();
	// // test_read(mem, size);
	// our_free(mem);
	// printf("Print free 1\n");
	// print_malloc_mem();
	// our_free(mem_2);
	// printf("Print free 2\n");

	// print_malloc_mem();
	// printf("Print free 3\n");
	// our_free(mem_large);
	// print_malloc_mem();

	// malloc_exit();
	// return (0);
}
