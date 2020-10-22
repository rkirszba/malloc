/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:50 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/22 19:01:02 by ldevelle         ###   ########.fr       */
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

	base->small.size = ZONE_SIZE;
	base->tiny.size = ZONE_SIZE / 4;

	if (ERROR == zone_create(&base->small.zone, base->small.size))
		return (ERROR);

	if (ERROR == zone_create(&(base->tiny.zone), base->tiny.size))
		return (ERROR);

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
