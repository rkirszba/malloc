/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:54:31 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/09 17:54:35 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static void		recur(size_t n, size_t base)
{
	if (n != 0)
	{
		recur(n / base, base);
		write(1, &"0123456789ABCDEF"[n % base], 1);
	}
}

void			print_hex_zeroes(size_t n)
{
	size_t		shift;

	shift = sizeof(size_t) * 2;
	shift -= 4;
	while (shift < sizeof(size_t) * 2
	&& 0 == (n & ((size_t)MASK_CHAR << shift)))
	{
		write(1, "0", 1);
		shift -= 4;
	}
}

void			print_dec(size_t n)
{
	recur(n, 10);
}

void			print_hex(size_t n)
{
	write(1, "0x", 2);
	recur(n, 16);
}
