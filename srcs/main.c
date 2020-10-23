/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:46 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/23 17:05:57 by ldevelle         ###   ########.fr       */
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


	print_malloc_mem();
	mem_2 = our_malloc(size * 2);


	print_malloc_mem();
	test_write(mem, size);
	// test_read(mem, size);

	test_write(mem_2, size *2);
	print_malloc_mem();
	// test_read(mem, size);
	our_free(mem);
	our_free(mem_2);

	print_malloc_mem();

	malloc_exit();
	return (0);
}
