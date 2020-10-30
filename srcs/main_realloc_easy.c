/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_realloc_easy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:57:19 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/30 17:36:22 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


int main(void)
{
	void *ptr;
	void *ptr2;

	ptr = our_malloc(213);
	printf("After first allocation, ptr = %p\n", ptr);
	ptr = our_realloc(ptr, 240);
	printf("After bigger reallocation with space, ptr = %p\n", ptr);
	ptr = our_realloc(ptr, 213);
	printf("After smaller reallocation, ptr = %p\n", ptr);
	ptr2 = our_malloc(213);
	ptr = our_realloc(ptr, 213);
	printf("After bigger reallocation without space, ptr = %p\n", ptr);
	return (0);
}