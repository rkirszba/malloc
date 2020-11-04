/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 20:19:47 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/03 15:09:08 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "head.h"

void    ft_memncpy(void* dest, const void* src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        ((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
        i++;
    }
}

static void    *realloc_cant(t_alloc_header *alloc_header, size_t size)
{
    void	*new_ptr;
	size_t	n;

    new_ptr = our_malloc(size);
	// printf("Hello1\n");
    if (new_ptr)
	{
		n = alloc_header->size <= size ? alloc_header->size : size;
        ft_memncpy(new_ptr, (void*)alloc_header + sizeof(t_alloc_header), n);
	}
	// printf("Hello2\n");
    our_free((void*)alloc_header + sizeof(t_alloc_header));
    return new_ptr;
}

static void    *realloc_smaller(t_alloc_header *alloc_header, size_t size)
{
    if (SUCCESS == alloc_split(alloc_header, size))
	{
		unavailable_remove(alloc_header);
		// alloc_set_unavailable(alloc_header);	/*
												// ** only because it is set to
												// ** available in unavailable remove
												// */
		unavailable_add(alloc_header);
		defragment(alloc_access_next(alloc_header));
        available_add(alloc_access_next(alloc_header));
	}
    return ((void*)alloc_header + sizeof(t_alloc_header));
}

static void    *realloc_can(t_alloc_header *alloc_header, size_t size)
{
    if (NULL == alloc_join_realloc(alloc_header, size))
		return (realloc_cant(alloc_header, size));
	unavailable_remove(alloc_header);
	// alloc_set_unavailable(alloc_header);	/*
											// ** only because it is set to
											// ** available in unavailable remove
											// */
	unavailable_add(alloc_header);
	return (realloc_smaller(alloc_header, size));
}


void	*our_realloc(void *ptr, size_t size)
{
    t_alloc_header  *alloc_header;
	t_mem_type		*mem_type;

	write(1, "hello+\n", 7);
    if (ptr == NULL || size == 0)
    {
        if (size == 0)
            our_free(ptr);
        return (our_malloc(size + 1));
    }
	// printf("HELLLO1\n");
	write(1, "hello0\n", 7);
    if (static_mem()->is_init != TRUE)
		malloc_init();
    alloc_header = ptr - sizeof(t_alloc_header);
	// printf("HELLLO2\n");
	write(1, "hello1\n", 7);
    if (unavailable_exists((void*)alloc_header) == FALSE)
        return (NULL);
    size = secure_align_size(size);
	mem_type = mem_type_get_from_size(size);
	write(1, "hello2\n", 7);
	// printf("HELLLO3\n");
	if ((!mem_type && !(alloc_header->flags & HDR_TYPE_LARGE))
	|| (mem_type && 0 == (alloc_header->flags & mem_type->type)))
	{
		write(1, "option0\n", 8);
		// printf("option1\n");
		return (realloc_cant(alloc_header, size));
	}
    else if (size <= alloc_header->size)
	{
		write(1, "option1\n", 8);
		// printf("option2\n");
        return (realloc_smaller(alloc_header, size));
	}
    else if (alloc_header->flags & HDR_TYPE_LARGE)
	{
		write(1, "option2\n", 8);
        return (realloc_cant(alloc_header, size));
	}
    else
	{
		write(1, "option3\n", 8);
		// printf("option4\n");
        return (realloc_can(alloc_header, size));
	}
}
