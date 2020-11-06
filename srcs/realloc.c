/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 20:19:47 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/06 14:57:39 by rkirszba         ###   ########.fr       */
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

	pthread_mutex_unlock(&static_mem()->lock);
    new_ptr = our_malloc(size);
	pthread_mutex_lock(&static_mem()->lock);
	if (new_ptr)
	{
		n = alloc_header->size <= size ? alloc_header->size : size;
        ft_memncpy(new_ptr, (void*)alloc_header + sizeof(t_alloc_header), n);
	}
	pthread_mutex_unlock(&static_mem()->lock);
    our_free((void*)alloc_header + sizeof(t_alloc_header));
	pthread_mutex_lock(&static_mem()->lock);
    return new_ptr;
}

static void    *realloc_smaller(t_alloc_header *alloc_header, size_t size)
{
    if (SUCCESS == alloc_split(alloc_header, size))
	{
		unavailable_remove(alloc_header);
		unavailable_add(alloc_header);
		defragment(alloc_access_next(alloc_header));
        available_add(alloc_access_next(alloc_header));
	}
    return ((void*)alloc_header + sizeof(t_alloc_header));
}

static void    *realloc_can(t_alloc_header *alloc_header, size_t size)
{
	void			*mem;

    if (NULL == alloc_join_realloc(alloc_header, size))
	{
		pthread_mutex_unlock(&static_mem()->lock);
		mem = realloc_cant(alloc_header, size);
	}
	else
	{
		unavailable_remove(alloc_header);
		unavailable_add(alloc_header);
		pthread_mutex_unlock(&static_mem()->lock);
		mem = realloc_smaller(alloc_header, size);
	}
	return (mem);
}


void	*our_realloc(void *ptr, size_t size)
{
    t_alloc_header  *alloc_header;
	t_mem_type		*mem_type;
	void			*mem;

    if (static_mem()->is_init != TRUE)
		malloc_init();
	pthread_mutex_lock(&static_mem()->lock);
    if (ptr == NULL || size == 0)
    {
		pthread_mutex_unlock(&static_mem()->lock);
        if (size == 0)
            our_free(ptr);
        return (our_malloc(size + 1));
    }
	mem = NULL;
    alloc_header = ptr - sizeof(t_alloc_header);
    if (unavailable_exists((void*)alloc_header) == FALSE)
	{
        return (NULL);
	}
    size = secure_align_size(size);
	mem_type = mem_type_get_from_size(size);
	if ((!mem_type && !(alloc_header->flags & HDR_TYPE_LARGE))
	|| (mem_type && 0 == (alloc_header->flags & mem_type->type)))
	{
		mem = realloc_cant(alloc_header, size);
	}
    else if (size <= alloc_header->size)
	{
        mem = realloc_smaller(alloc_header, size);
	}
    else if (alloc_header->flags & HDR_TYPE_LARGE)
	{
        mem = realloc_cant(alloc_header, size);
	}
    else
	{
        mem = realloc_can(alloc_header, size);
	}
	pthread_mutex_unlock(&static_mem()->lock);
	return (mem);
}
