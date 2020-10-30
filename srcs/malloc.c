/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:50 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/30 11:24:31 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int8_t		malloc_exit(void)
{
	t_infos			*base;
	int8_t			retval;

	retval = SUCCESS;
	base = static_mem();
	if (ERROR == zone_liberate_all(base->small.zone))
		retval = ERROR;
	if (ERROR == zone_liberate_all(base->tiny.zone))
		retval = ERROR;
	if (ERROR == zone_liberate_all(base->large))
		retval = ERROR;
	return (retval);
}

void		malloc_init(void)
{
	t_infos	*base;

	base = static_mem();

	mem_type_init(&base->tiny, ZONE_TINY);
	mem_type_init(&base->small, ZONE_SMALL);

	base->is_init = TRUE;
}

void		*our_malloc(size_t size)
{
	void	*mem;

	if (static_mem()->is_init != TRUE)
		malloc_init();
	mem = alloc_get(size);
	if (mem)
		return (mem + sizeof(t_alloc_header));
	return (NULL);
}
