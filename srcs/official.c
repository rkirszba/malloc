/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:07:39 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/13 16:37:56 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void		*malloc(size_t size)
{
	void	*mem;

	mem = our_malloc(size);
	return (mem);
}

void		*realloc(void *ptr, size_t size)
{
	void	*mem;

	mem = our_realloc(ptr, size);
	return (mem);
}

void		free(void *ptr)
{
	our_free(ptr);
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

	mem = our_calloc(count, size);
	if (mem)
		ft_bzero(mem, secure_align_size(count * size));
	return (mem);
}
