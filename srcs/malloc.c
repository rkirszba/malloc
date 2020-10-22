/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:00:50 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/22 15:14:42 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int8_t		malloc_exit(void)
{
	t_malloc	*base;
	int8_t			retval;

	retval = SUCCESS;
	base = *static_mem();
	if (ERROR == zone_liberate_all(base->small_zone, base->small_zone_size))
		retval = ERROR;
	if (ERROR == zone_liberate_all(base->tiny_zone, base->tiny_zone_size))
		retval = ERROR;
    if (-1 == munmap((void*)base, sizeof(t_malloc)))
		retval = ERROR;
	return (retval);
}

int8_t		malloc_init(void)
{
	t_malloc	*base;

    base = mmap(NULL, sizeof(t_malloc), PROT_READ | PROT_WRITE,
				MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if (base == MAP_FAILED)
		return (ERROR);

	*static_mem() = (t_malloc*)base;

	base->small_zone_size = ZONE_SIZE;
	base->tiny_zone_size = ZONE_SIZE / 4;

	if (ERROR == zone_create(&base->small_zone, base->small_zone_size))
		return (ERROR);

	if (ERROR == zone_create(&(base->tiny_zone), base->tiny_zone_size))
		return (ERROR);

	return (SUCCESS);
}

void		*our_malloc(size_t size)
{
	void	*mem;

	if (*static_mem() == NULL)
		if (malloc_init() == ERROR)
			return ((void*)ERROR);

	mem = get_spot(size);
	return (mem);
	return (malloc(size));
}
