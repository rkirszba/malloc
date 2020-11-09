/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_set_availability.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:28:39 by ldevelle          #+#    #+#             */
/*   Updated: 2020/11/09 17:23:45 by ezalos           ###   ########.fr       */
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
