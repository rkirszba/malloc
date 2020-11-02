/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rand_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:01:26 by arobion           #+#    #+#             */
/*   Updated: 2020/10/31 12:31:07 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE_TAB	10000
#define NB_TEST		1000000
#define SIZE_ALLOC	16


int			get_size_alloc()
{
	return (rand() % (2 << 16));
}

void		test_write2(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((char*)mem)[i++] = size;
}


int8_t		unit_test(char **tab, int index)
{
	size_t		size;
	int			r;

	r = rand() % SIZE_TAB;
	(void)index;
	size = get_size_alloc();
	
	if (!(tab[r] = our_realloc(tab[r], size)))
		return (ERROR);
	test_write2(tab[r], secure_align_size(size));
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
		our_free(tab[i]);
		i++;
	}
	write(1, "e", 1);
	our_free(tab);

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
	else
		nb_tests = NB_TEST;
	srand(17);

	write(1, "Begin tests\n", 12);
	printf("SIZE TAB = %d\n", SIZE_TAB);
	if (!(tab = init()))
		return (10);
	write(1, "\n", 1);
	i = -1;
	while (++i < nb_tests)
	{
		if (0 == i % 1000)
			printf("%d\n", i);
		if (ERROR == unit_test(tab, i))
			return (10);
	}
	write(1, "\n", 1);
	finish(tab);

	write(1, "\nEnd tests\n", 11);
	return (0);
}
