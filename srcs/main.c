/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:46 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 02:36:33 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int		main(int ac, char **av)
{
	int		size;
	void	*mem;
	void	*mem_2;

	if (ac != 2)
		return (0);
	size = atoi(av[1]);
	mem = our_malloc(size);

	printf("We got mem %p\n", mem);
	print_malloc_mem();
	mem_2 = our_malloc(size * 2);
	printf("We got mem2 %p\n", mem_2);


	print_malloc_mem();
	test_write(mem, size);
	// test_read(mem, size);

	test_write(mem_2, size *2);
	printf("Print test write\n");
	print_malloc_mem();
	// test_read(mem, size);
	our_free(mem);
	printf("Print free 1\n");
	print_malloc_mem();
	our_free(mem_2);
	printf("Print free 2\n");

	print_malloc_mem();

	malloc_exit();
	return (0);
}
