/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:31:17 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/30 17:23:48 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    void    *ptr;

    // free(NULL);
    // ptr = malloc(16);
    // printf("%p\n", ptr);
    ptr = malloc(0);
    printf("%p\n", ptr);
}