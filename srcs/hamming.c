/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hamming.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 14:24:04 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/02 18:16:16 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

uint8_t		parity_of_bit_n(uint8_t *data, size_t size, uint8_t n)
{
	size_t		i;
	uint8_t		parity;

	i = 0;
	parity = 0;
	while (i < size)
	{
		if (data[i] & (1 << n))
			parity = !parity;
		i++;
	}
	return (parity);
}

uint8_t		parity_of_oct(uint8_t octet)
{
	size_t		i;
	uint8_t		parity;

	i = 0;
	parity = 0;
	while (i < 8)
	{
		if (octet & (1 << i))
			parity = !parity;
		i++;
	}
	return (parity);
}

uint8_t		parity_of_oct_n(uint8_t *data, size_t size, uint8_t n)
{
	size_t		i;
	uint8_t		parity;

	i = 0;
	parity = 0;
	while (i < size)
	{
		if (i & (1 << n))
			if (parity_of_oct(data[i]))
				parity = !parity;
		i++;
	}
	return (parity);
}

uint8_t			parity_of_obj(uint8_t *data, size_t size, uint8_t type)
{
	uint8_t		hamming;
	size_t		i;

	hamming = 0;
	i = 0;
	while (i < 8)
	{
		if ((type && parity_of_oct_n(data, size, i))
		|| (!type && parity_of_bit_n(data, size, i)))
			hamming |= (1 << i);
		i++;
	}
	return (hamming);
}

void			hamming_do(uint8_t *data, size_t size, uint8_t *hamming)
{
	uint8_t		parity_bit;
	uint8_t		parity_oct;

	hamming[0] = 0;
	hamming[1] = 0;
	parity_bit = parity_of_obj(data, size, 0);
	parity_oct = parity_of_obj(data, size, 1);
	hamming[0] = parity_bit;
	hamming[1] = parity_oct;
}

int8_t			hamming_check(uint8_t *data, size_t size, uint8_t *hamming)
{
	int8_t		retval;
	uint8_t		parity_bit;
	uint8_t		parity_oct;

	retval = SUCCESS;
	parity_bit = hamming[0];
	parity_oct = hamming[1];
	hamming[0] = 0;
	hamming[1] = 0;
	hamming_do(data, size, hamming);
	if (parity_bit != hamming[0])
		retval = FAILURE;
	if (parity_oct != hamming[1])
		retval = FAILURE;
	if (retval == FAILURE)
		write(1, "@@@@@-----CORRUPTED HEADER-----@@@@@\n", 37);
	return (retval);
}
