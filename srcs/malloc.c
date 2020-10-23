/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:50 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/23 16:38:28 by ldevelle         ###   ########.fr       */
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

	// printf("Hello in\n");
	mem_type_init(&base->small, ZONE_SMALL);
	if (ERROR == zone_create(&base->small, ZONE_SMALL))
		return (ERROR);

	// printf("Hello small done\n");

	mem_type_init(&base->tiny, ZONE_TINY);
	if (ERROR == zone_create(&base->tiny, ZONE_TINY))
		return (ERROR);
	// printf("Hello tiny dßone\n");

	return (SUCCESS);
}

void		*our_malloc(size_t size)
{
	void	*mem;

	if (static_mem()->small.zone == NULL)
		if (malloc_init() == ERROR)
			return ((void*)ERROR);

	mem = get_spot(size);
	return (mem);
}
