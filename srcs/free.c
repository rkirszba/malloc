/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:27:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/23 15:25:00 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_alloc_header	*defragment(t_alloc_header *alloc_header)
{
	t_alloc_header	*neighbor;
	
	neighbor = alloc_access_next(alloc_header);
	if (neighbor && neighbor->available)
	{
		alloc_header = alloc_join(alloc_header, TRUE);
		remove_available((void*)neighbor);
		return defragment(alloc_header);
	}
	neighbor = alloc_access_prev(alloc_header);
	if (neighbor && neighbor->available)
	{
		alloc_header = alloc_join(neighbor, TRUE);
		remove_available((void*)neighbor);
	}
	return alloc_header;
}


void	our_free(void *ptr)
{
	t_infos			*infos;
	t_alloc_header	*alloc_header;
	t_rbt			**tree;
	t_rbt			*node;

	alloc_header = ptr - sizeof(t_alloc_header)
	if (remove_unavailable((void*)alloc_header)) == FAILURE)
		return ;
	alloc_header = defragment(alloc_header);
	add_available(alloc_header);
}


