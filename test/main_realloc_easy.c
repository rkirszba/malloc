/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_realloc_easy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:57:19 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/31 11:52:07 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"


int main(void)
{
	void *ptr;
	void *ptr2;

	ptr = our_malloc(151);
	printf("After first allocation\n");
	printf("ptr = %p\n", ptr);
	show_alloc_mem();
	printf("\n\n");
	// sleep(5);

	ptr = our_realloc(ptr, 233);
	printf("After bigger reallocation with space\n");
	printf("ptr = %p\n", ptr);
	show_alloc_mem();
	printf("\n\n");
	// sleep(5);

	ptr = our_realloc(ptr, 151);
	printf("After smaller reallocation\n");
	printf("ptr = %p\n", ptr);
	show_alloc_mem();
	printf("\n\n");
	// sleep(5);

	ptr2 = our_malloc(125);
	printf("After new malloc reallocation\n");
	printf("ptr2 = %p\n", ptr2);
	show_alloc_mem();
	printf("\n\n");
	// sleep(5);

	ptr = our_realloc(ptr, 273);
	printf("After bigger reallocation without space\n");
	printf("ptr = %p\n", ptr);
	show_alloc_mem();
	printf("\n\n");

	our_free(ptr);
	printf("After free of ptre\n");
	show_alloc_mem();
	printf("\n\n");

/*
	ptr = our_malloc(125);
	show_alloc_mem();
	printf("\n\n");

	ptr2 = our_malloc(273);
	show_alloc_mem();
	printf("\n\n");

	our_free(ptr);
	show_alloc_mem();
*/

	return (0);
}