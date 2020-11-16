/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:41:44 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/16 12:40:07 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void			ft_memncpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
}

void		ft_bzero(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((char*)mem)[i++] = 0;
}

size_t			hash_djb2(unsigned char *ptr)
{
	ssize_t			i;
	unsigned long	hash;

	i = -1;
	hash = 5381;
	while (++i < 8)
	{
		hash = ((hash << 5) + hash) + ptr[i];
	}
	return (hash);
}
