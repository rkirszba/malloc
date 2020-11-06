/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <arobion@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:01:26 by arobion           #+#    #+#             */
/*   Updated: 2020/11/05 14:08:49 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE_TAB	5000
#define NB_TEST		1000000
#define SIZE_ALLOC	16
#define TINY		(RES_TINY * TINY_SIZE_MAX_FACTOR)
#define SMALL		(RES_SMALL * SMALL_SIZE_MAX_FACTOR)

size_t		size_tab[SIZE_TAB];

size_t			get_size_alloc()
{
	size_t	size_type;
	size_t	size;

	size_type = 3;
	while (size_type == 3)
		size_type = rand() % 3;
	if (size_type == 0)
		size = (size_t)rand() % TINY;
	else if (size_type == 1)
		size = TINY + ((size_t)rand() % (SMALL - TINY));
	else
		size = SMALL + ((size_t)rand() % (2 << 18));
	printf("%6lu", size);
	return (size);
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
		{
			write(1, "ERROR USER MEMORY HAS BEEN ALTERED\n", 35);
			break;
		}
}



int8_t		unit_test_malloc(t_alloc_header **tab)
{
	size_t		old;
	int			r;

	r = rand() % SIZE_TAB;
	printf("%-5d ", r);
	test_read2(tab[r], secure_align_size(size_tab[r]));
	our_free(tab[r]);
	old = size_tab[r];
	size_tab[r] = get_size_alloc();
	printf(" (%6lu)", old);
	old = (size_t)tab[r];
	if (!(tab[r] = our_malloc(size_tab[r])))
		return (ERROR);
	printf(" %p", tab[r]);
	printf(" (%p)", (void*)old);
	test_write2(tab[r], secure_align_size(size_tab[r]));
	return (SUCCESS);
}

int8_t		unit_test_realloc(t_alloc_header **tab)
{
	size_t		old;
	int			r;

	r = rand() % SIZE_TAB;
	printf("%-5d ", r);
	test_read2(tab[r], secure_align_size(size_tab[r]));
	old = size_tab[r];
	size_tab[r] = get_size_alloc();
	printf(" (%6lu)", old);
	old = (size_t)tab[r];
	if (!(tab[r] = our_realloc(tab[r], size_tab[r])))
		return (ERROR);
	printf(" %p", tab[r]);
	printf(" (%p)", (void*)old);
	test_write2(tab[r], secure_align_size(size_tab[r]));
	return (SUCCESS);
}

int8_t		unit_test(t_alloc_header **tab)
{
	size_t	type;
	int8_t	retval;

	type = rand() % 100;
	if (type < 35)
	{
		printf("realloc: ");
		retval = unit_test_realloc(tab);
	}
	else
	{
		printf("malloc:  ");
		retval = unit_test_malloc(tab);
	}
	type = rand() % 100;
	if (type > 100)
		our_free((void*)(((size_t)rand() << 32) + (size_t)rand()));
	printf(" %d\n", retval);
	return (retval);
}

t_alloc_header		**init(void)
{
	t_alloc_header		**tab;
	int					i;

	if (!(tab = our_malloc(sizeof(void *) * SIZE_TAB)))
		return (NULL);
	i = 0;
	write(1, "\n", 1);
	while (i < SIZE_TAB)
	{
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
		our_free(tab[i]);
		i++;
	}
	our_free(tab);
}

# define THRED_NB	4

int			main(int ac, char **av)
{
	t_alloc_header		**tab;
	int			i;
	int			nb_tests = NB_TEST;

	if (ac > 1)
		nb_tests = atoi(av[1]);
	else
		nb_tests = NB_TEST;
	if (ac > 2)
		srand(atoi(av[2]));
	else
		srand(17);

	if (!(tab = init()))
		return (10);
	write(1, "\n", 1);
	if (THRED_NB > 1)
	{
		i = -1;

	}
	i = -1;
	while (++i < nb_tests)
	{
		if (0 == i % 1000)
			printf("%d\n", i);
		if (ERROR == unit_test(tab))
			return (10);
	}
	finish(tab);
	return (0);
}
