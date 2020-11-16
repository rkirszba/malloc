/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:12:28 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:12:29 by rkirszba         ###   ########.fr       */
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

void		*calloc(size_t count, size_t size)
{
	void	*mem;

	mem = our_calloc(count, size);
	return (mem);
}
