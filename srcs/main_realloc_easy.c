/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_realloc_easy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:57:19 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/30 18:11:54 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


int main(void)
{
	void *ptr;
	void *ptr2;

	ptr = our_malloc(151);
	printf("After first allocation, ptr = %p\n", ptr);
	show_alloc_mem();
	printf("\n\n");
	ptr = our_realloc(ptr, 233);
	printf("After bigger reallocation with space, ptr = %p\n", ptr);
	show_alloc_mem();
	printf("\n\n");
	ptr = our_realloc(ptr, 151);
	printf("After smaller reallocation, ptr = %p\n", ptr);
	show_alloc_mem();
	printf("\n\n");
	ptr2 = our_malloc(213);
	ptr = our_realloc(ptr, 213);
	printf("After bigger reallocation without space, ptr = %p\n", ptr);
	show_alloc_mem();
	printf("\n\n");
	return (0);
}