/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:07:39 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/02 18:44:06 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void		*malloc(size_t size)
{
	void	*mem;

	write(1, "mHello World\n", 13);
	mem = our_malloc(size);
	write(1, "mByeby World\n", 13);
	return (mem);
}

void		*realloc(void *ptr, size_t size)
{
	void	*mem;

	write(1, "rHello World\n", 13);
	mem = our_realloc(ptr, size);
	write(1, "rByeby World\n", 13);
	return (mem);
}

void		free(void *ptr)
{
	write(1, "fHello World\n", 13);
	our_free(ptr);
	write(1, "fByeby World\n", 13);
}


void		ft_bzero(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((char*)mem)[i++] = 0x42;
}

void		*calloc(size_t count, size_t size)
{
	void	*mem;
	write(1, "cHello World\n", 13);
	if (size == 0 || count == 0)
		return (NULL);

	if (static_mem()->is_init != TRUE)
		malloc_init();

	size = secure_align_size(size);
	// size = (((size - 1) >> 4) << 4) + 16;
	// size = (((size - 1) >> 3) << 3) + 8;
	// size = (((size - 1) >> 2) << 2) + 4;
	mem = our_malloc(count * size);
	if (mem)
		ft_bzero(mem, secure_align_size(count * size));
	write(1, "cByeby World\n", 13);
	return (mem);
}
