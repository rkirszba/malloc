/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:07:39 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/02 11:57:32 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void		*malloc(size_t size)
{
	// write(1, "mHello World\n", 13);
	return (our_malloc(size));
}

void		*realloc(void *ptr, size_t size)
{
	// write(1, "rHello World\n", 13);
	return (our_realloc(ptr, size));
}

void		free(void *ptr)
{
	// write(1, "fHello World\n", 13);
	our_free(ptr);
}

void		*calloc(size_t count, size_t size)
{
	// write(1, "cHello World\n", 13);
	if (size == 0 || count == 0)
		return (NULL);

	size = (((size - 1) >> 3) << 3) + 8;
	return (our_malloc(count * size));
}
