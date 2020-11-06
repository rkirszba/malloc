/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:06:07 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/06 16:08:46 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


void		test_write(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((char*)mem)[i++] = (uint8_t)size;
}

void		test_read(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		if (((uint8_t*)mem)[i++] != (uint8_t)size)
		{
			write(1, "ERROR USER MEMORY HAS BEEN ALTERED\n", 35);
			break;
		}
}
