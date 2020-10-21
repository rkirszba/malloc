/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_malloc_random.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arobion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:01:26 by arobion           #+#    #+#             */
/*   Updated: 2020/10/21 15:15:35 by arobion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <time.h>

#define SIZE_TAB 20000
#define NB_TEST 10000000
#define SIZE_ALLOC 16

int get_size_alloc()
{
	return rand() % (2 ^ 16);
}

int main(void)
{
	char		**tab;
	int			i;
	int			r;
	srand(42);
// 	srand(time(NULL));

	if (!(tab = malloc(sizeof(void *) * SIZE_TAB)))
		return (10);
	i = 0;
	while (i < SIZE_TAB)
	{
		if (!(tab[i] = malloc(SIZE_ALLOC)))
			return (10);
		tab[i][0] = 'a';
		i++;
	}
	i = 0;
	while (i < NB_TEST)
	{
		r = rand() % SIZE_TAB;
		free(tab[r]);
		if (!(tab[r] = malloc(SIZE_ALLOC)))
			return (10);
		tab[r][0] = 'a';
		i++;
	}
	i = 0;
	while (i < SIZE_TAB)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}
