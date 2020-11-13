/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:16:30 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/13 16:50:27 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


void	*our_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (size == 0 || count == 0)
		return (our_malloc(0));
	if (static_mem()->is_init != TRUE)
		malloc_init();
	total_size = count * size;
	ptr = our_malloc(total_size);
	if (ptr)
		ft_bzero(ptr, secure_align_size(total_size));
	return (ptr);
}
