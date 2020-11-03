/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   official.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 21:07:39 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/02 23:35:46 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putnbr(size_t nbr)
{
	if (nbr / 10)
		ft_putnbr(nbr / 10);
	ft_putchar((char)(nbr % 10 + '0'));
}

void		*malloc(size_t size)
{
	void	*mem;
	size_t	aligned_size;

	write(1, "mHello World\n", 13);
	mem = our_malloc(size);
	aligned_size = ((t_alloc_header*)(mem - sizeof(t_alloc_header)))->size;

	write(1, "GIVEN size = ", 13);
	ft_putnbr(aligned_size);
	write(1, "\n", 1);
	write(1, "      size = ", 13);
	ft_putnbr(size);
	write(1, "\n", 1);
	if (((t_alloc_header*)(mem - sizeof(t_alloc_header)))->flags & HDR_POS_LAST)
		write(1,"IT IS THE LAST ELEMENT\n", 23);
	if (aligned_size < size)
		write(1, "ALIGNED SIZE SMALLER THAN SIZE !!!\n", 35);
	if (aligned_size % 8)
		write(1, "ALIGNED SIZE IS NOT MODULO 8\n", 29);
	write(1, "mByeby World\n", 13);
	return (mem);
}

void		*realloc(void *ptr, size_t size)
{
	void	*mem;
	size_t	aligned_size;

	write(1, "rHello World\n", 13);
	mem = our_realloc(ptr, size);
	aligned_size = ((t_alloc_header*)(mem - sizeof(t_alloc_header)))->size;
	write(1, "GIVEN size = ", 13);
	ft_putnbr(aligned_size);
	write(1, "\n", 1);
	write(1, "      size = ", 13);
	ft_putnbr(size);
	write(1, "\n", 1);
	if (((t_alloc_header*)(mem - sizeof(t_alloc_header)))->flags & HDR_POS_LAST)
		write(1,"IT IS THE LAST ELEMENT\n", 23);
	if (aligned_size < size)
		write(1, "ALIGNED SIZE SMALLER THAN SIZE !!!\n", 35);
		if (aligned_size % 8)
	write(1, "ALIGNED SIZE IS NOT MODULO 8\n", 29);
	write(1, "rByeby World\n", 13);
	return (mem);
}

void		free(void *ptr)
{
	write(1, "fHello World\n", 13);
	our_free(ptr);
	write(1, "fByeby World\n", 13);
}


void		ft_bzero(void *mem, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		((char*)mem)[i++] = 0;
}

void		*calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	tmp_size;
	size_t	aligned_size;

	write(1, "cHello World\n", 13);
	if (size == 0 || count == 0)
		return (NULL);

	if (static_mem()->is_init != TRUE)
		malloc_init();
	write(1, "size = ", 7);
	ft_putnbr(size);
	write(1, "\n", 1);
	write(1, "count = ", 8);
	ft_putnbr(count);
	write(1, "\n", 1);
	tmp_size = size;
	size = secure_align_size(size);
	// size = (((size - 1) >> 4) << 4) + 16;
	// size = (((size - 1) >> 3) << 3) + 8;
	// size = (((size - 1) >> 2) << 2) + 4;
	mem = our_malloc(count * size);
	aligned_size = ((t_alloc_header*)(mem - sizeof(t_alloc_header)))->size;
	write(1, "GIVEN size = ", 13);
	ft_putnbr(aligned_size);
	write(1, "\n", 1);
	write(1, "      size = ", 13);
	ft_putnbr(tmp_size * count);
	write(1, "\n", 1);
	if (((t_alloc_header*)(mem - sizeof(t_alloc_header)))->flags & HDR_POS_LAST)
		write(1,"IT IS THE LAST ELEMENT\n", 23);
	if (aligned_size < size)
		write(1, "GIVEN SIZE SMALLER THAN SIZE !!!\n", 35);
	if (aligned_size % 8)
		write(1, "ALIGNED SIZE IS NOT MODULO 8\n", 29);
	if (mem)
		ft_bzero(mem, secure_align_size(count * size));
	write(1, "cByeby World\n", 13);
	return (mem);
}
