/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 20:19:47 by rkirszba          #+#    #+#             */
/*   Updated: 2020/10/26 20:33:52 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "head.h"

void    ft_memncpy(void* dest, void* src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        ((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
        i++;
    }
}

void    *realloc(void* ptr, size_t size)
{
    t_alloc_header  *alloc_header;
    void            *new_ptr;

    if (static_mem()->is_init != TRUE)
		return NULL;
    alloc_header = ptr - sizeof(t_alloc_header);
    if (unavailable_exists((void*)alloc_header) == FALSE)
        return NULL;
    // faire un if avec tentative de join
        // remove le next header
        // remove alloc_header
        // split
            // si marche, ajout du next header
        // add new_alloc header 
    else
    {
        new_ptr = our_malloc(size);
        our_free(ptr);
        ft_memncpy(new_ptr, ptr, alloc_header->size);
        return new_ptr
    }
    return NULL;
}