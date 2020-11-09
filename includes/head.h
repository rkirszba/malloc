/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/11/09 17:51:10 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include <sys/mman.h>
# include <stddef.h>
# include <stddef.h>
# include <inttypes.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include "tree.h"

/*
**	BASE
*/

# define ERROR						-1
# define FAILURE					-1
# define SUCCESS					0
# define TRUE						1
# define FALSE						0

/*
**	PRINTING
*/

# define PRINT_LINE_SIZE			(32 * 4)
# define MASK_CHAR					0b1111

/*
**	ALLOC FLAGS
*/

# define HDR_POS					0b00000011
# define HDR_POS_FIRST				0b00000001
# define HDR_POS_LAST				0b00000010
# define HDR_AVAILABLE				0b00000100
# define HDR_UNAVAILABLE			0b00000000
# define HDR_TYPE					0b00111000
# define HDR_TYPE_TINY				0b00001000
# define HDR_TYPE_SMALL				0b00010000
# define HDR_TYPE_LARGE				0b00100000

/*
**	ALLOC FLAGS
*/


# define ZONE_TINY					HDR_TYPE_TINY
# define ZONE_SMALL					HDR_TYPE_SMALL
# define ZONE_LARGE					HDR_TYPE_LARGE

/*
**	MEM TYPE values
*/

// # define ZONE_SIZE					4096
# define TINY_SIZE_MAX_FACTOR		32
# define SMALL_SIZE_MAX_FACTOR		32
# define RES_TINY					16
# define RES_TINY_SHIFT				4
# define RES_SMALL					512
# define RES_SMALL_SHIFT			9
# define RES_LARGE					4096
# define RES_LARGE_SHIFT			12
# define SIZE_TINY					2097152
# define SIZE_SMALL					16777216

/*
**	UNAVAILABLE/AVAILABLE DATA STRUCTURE
*/

# define TAB_ALLOCS 				77777
# define AVAILABLE_TABLE_SIZE		(SMALL_SIZE_MAX_FACTOR > TINY_SIZE_MAX_FACTOR ? SMALL_SIZE_MAX_FACTOR : TINY_SIZE_MAX_FACTOR) + 1
# define UNAVAILABLE_TABLE_SIZE		13


typedef	struct				s_alloc_header
{
	t_rbt					rbt;
	uint32_t				size;
	uint32_t				size_prev;
	uint8_t					flags;
	uint16_t				parity_bit;
}							t_alloc_header;

typedef	struct				s_zone_header
{
	struct s_zone			*next_zone;
	struct s_zone			*prev_zone;
	size_t					size;
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

# include "prototypes_malloc.h"

#endif
