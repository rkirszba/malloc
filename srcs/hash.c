/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:23:30 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/10 16:13:49 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

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
