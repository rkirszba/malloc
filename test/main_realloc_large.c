/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_realloc_large.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 00:15:04 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/03 00:28:11 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	main(int ac, char **av)
{
	void	*ptr;
	
	(void)ac;
	(void)av;
	ptr = our_malloc(300000);
	printf("ptr = %p\n", ptr);
	show_alloc_mem();
	ptr = our_realloc(ptr, 45000);
	show_alloc_mem();
	printf("ptr = %p\n", ptr);
	return (0);
}