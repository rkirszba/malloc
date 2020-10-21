/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 11:59:18 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/21 12:14:38 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

/*
**	Add a new entry to the memory index
*/

int8_t		mem_index_add(t_alloc *availble_alloc)
{
	int8_t		retval;

	retval = SUCCESS;
	(void)availble_alloc;
	return (retval);
}

/*
**	Remove an entry from the memory index
*/

uint8_t		mem_index_del(t_alloc *unavailble_alloc)
{
	int8_t		retval;

	retval = SUCCESS;
	(void)unavailble_alloc;
	return (retval);
}

/*
**	Return an entry from the memory index.
**
**	The returned entry is the closest superior size
**	compared to the 'size' argument
**
**	If no entry is available, return NULL.
*/

t_alloc		*mem_index_get(size_t size)
{
	t_alloc		*alloc;

	alloc = NULL;
	(void)size;
	return (alloc);
}
