/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:16:30 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/10 18:39:34 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


void	*our_calloc(size_t count, size_t size)
{
	size_t	total_size;
	// size_t	tmp_size;
	void	*ptr;
	// size_t	i;

	// i = 0;
	// tmp_size = 0;
	// total_size = 0;
	// size = secure_align_size(size);
	// count = secure_align_size(count);
	// while (i < count)
	// {
	// 	total_size += size;
	// 	if (total_size < tmp_size)
	// 	{
	// 		write(1, "!!!!!! OVERFLOWW !!!!!!\n", 24);
	// 		write(2, "!!!!!! OVERFLOWW !!!!!!\n", 24);
	// 		return (NULL);
	// 	}
	// 	tmp_size = total_size;
	// 	i++;
	// }
	// total_size = secure_align_size(total_size);
	if (size == 0 || count == 0)
		return (our_malloc(0));
	if (static_mem()->is_init != TRUE)
		malloc_init();
	// size = secure_align_size(size);
	// count = secure_align_size(count);
	// total_size = secure_align_size(size * count);
	total_size = count * size;
	ptr = our_malloc(total_size);
	
	ft_bzero(ptr, total_size);
	return (ptr);
}