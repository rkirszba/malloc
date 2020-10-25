/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:50 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/25 12:52:20 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int8_t		malloc_exit(void)
{
	t_infos			*base;
	int8_t			retval;

	retval = SUCCESS;
	base = static_mem();
	if (ERROR == zone_liberate_all(base->small.zone, base->small.size))
		retval = ERROR;
	if (ERROR == zone_liberate_all(base->tiny.zone, base->tiny.size))
		retval = ERROR;
    if (-1 == munmap((void*)base, sizeof(t_infos)))
		retval = ERROR;
	return (retval);
}

int8_t		malloc_init(void)
{
	t_infos	*base;

	base = static_mem();

	mem_type_init(&base->small, ZONE_SMALL);
	mem_type_init(&base->tiny, ZONE_TINY);

	base->is_init = TRUE;
	return (SUCCESS);
}

void		*our_malloc(size_t size)
{
	void	*mem;

	if (static_mem()->is_init != TRUE)
		if (malloc_init() == ERROR)
			return ((void*)ERROR);
	mem = alloc_get(size);
	if (mem)
		return (mem + sizeof(t_alloc_header));
	return (NULL);
}
