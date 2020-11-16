/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_set_availability.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:11:46 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:11:47 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void				alloc_set_available(t_alloc_header *alloc)
{
	alloc->flags = flag_set_availabilty(alloc->flags, HDR_AVAILABLE);
}

void				alloc_set_unavailable(t_alloc_header *alloc)
{
	alloc->flags = flag_set_availabilty(alloc->flags, HDR_UNAVAILABLE);
}
