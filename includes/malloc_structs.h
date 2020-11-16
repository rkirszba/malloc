/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:04:19 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/16 15:59:15 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_STRUCTS_H
# define MALLOC_STRUCTS_H

typedef	struct				s_alloc_header
{
	t_rbt					rbt;
	uint16_t				size;
	uint16_t				size_prev;
	uint8_t					flags;
}							t_alloc_header;

typedef	struct				s_zone_header
{
	struct s_zone			*next_zone;
	struct s_zone			*prev_zone;
	size_t					size;
	void					*aligner;
}							t_zone_header;

typedef	struct				s_zone
{
	t_zone_header			header;
	t_alloc_header			first_alloc_header;
}							t_zone;

typedef	struct				s_mem_type
{
	t_zone					*zone;
	size_t					size;
	size_t					alloc_size_min;
	size_t					alloc_size_max;
	size_t					factor_size_max;
	size_t					alloc_resolution_size;
	t_rbt					*available[AVAILABLE_TABLE_SIZE];
	uint8_t					type;
}							t_mem_type;

typedef	struct				s_infos
{
	t_mem_type				tiny;
	t_mem_type				small;
	t_zone					*large;
	t_rbt					*unavailable[UNAVAILABLE_TABLE_SIZE];
	pthread_mutex_t			lock;
	uint8_t					is_init;
}							t_infos;

typedef struct				s_alloc_test
{
	pthread_t				thread_nb;
	void					*mem;
	void					*old_mem;
	size_t					size;
	size_t					old_size;
	uint8_t					test_type;
	uint8_t					old_test_type;
	uint8_t					retval;

}							t_alloc_test;

#endif
