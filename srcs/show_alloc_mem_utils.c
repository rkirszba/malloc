/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:13:34 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:13:35 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

size_t			first_biggest_than(t_zone *zone, size_t bound)
{
	size_t		smallest;

	smallest = -1;
	while (zone)
	{
		if ((size_t)zone > bound && (size_t)zone < smallest)
			smallest = (size_t)zone;
		zone = zone->header.next_zone;
	}
	return (smallest);
}

t_zone			*next_smallest(size_t smallest)
{
	size_t		tiny;
	size_t		small;
	size_t		large;
	t_zone		*winner;

	tiny = first_biggest_than(static_mem()->tiny.zone, smallest);
	small = first_biggest_than(static_mem()->small.zone, smallest);
	large = first_biggest_than(static_mem()->large, smallest);
	if (tiny < small)
	{
		if (tiny < large)
			winner = (t_zone*)tiny;
		else
			winner = (t_zone*)large;
	}
	else
	{
		if (small < large)
			winner = (t_zone*)small;
		else
			winner = (t_zone*)large;
	}
	return (winner);
}
