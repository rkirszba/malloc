/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/25 01:57:23 by ezalos           ###   ########.fr       */
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
# include "tree.h"

# define ZONE_SIZE					4096

# define TINY__SIZE_MAX_FACTOR		32
# define SMALL_SIZE_MAX_FACTOR		32

# define AVAILABLE_TABLE_SIZE		(SMALL_SIZE_MAX_FACTOR > TINY__SIZE_MAX_FACTOR ? SMALL_SIZE_MAX_FACTOR : TINY__SIZE_MAX_FACTOR) + 1
# define UNAVAILABLE_TABLE_SIZE		77777

# define ERROR						-1
# define FAILURE					-1
# define SUCCESS					0

# define TRUE						1
# define FALSE						0

# define TAB_ALLOCS 				77777

# define PRINT_LINE_SIZE			32

# define ABS(x)						((x < 0) ? -x : x)

# define HDR_POS					0b00000011
# define HDR_POS_FIRST				0b00000001
# define HDR_POS_LAST				0b00000010
# define HDR_AVAILABLE				0b00000100
# define HDR_UNAVAILABLE			0b00000000
# define HDR_TYPE					0b00111000
# define HDR_TYPE_TINY				0b00001000
# define HDR_TYPE_SMALL				0b00010000
# define HDR_TYPE_LARGE				0b00100000

# define ZONE_TINY					HDR_TYPE_TINY
# define ZONE_SMALL					HDR_TYPE_SMALL
# define ZONE_LARGE					HDR_TYPE_LARGE


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
	size_t					used_size;
}							t_zone_header;

typedef	struct				s_zone
{
	t_zone_header			header;
	t_alloc_header			first_alloc_header;
	//uint8_t				first allocation memory of 'size' octets of memory;
}							t_zone;

typedef	struct				s_mem_type
{
	t_zone					*zone;
	size_t					size;
	size_t					alloc_size_min;
	size_t					alloc_size_max;
	size_t					factor_size_max;
	size_t					alloc_resolution_size;//minimal size without counting header
	t_rbt					*available[AVAILABLE_TABLE_SIZE];
	uint8_t					type;
}							t_mem_type;

typedef	struct				s_infos
{
	t_mem_type				tiny;
	t_mem_type				small;
	t_rbt					*unavailable[UNAVAILABLE_TABLE_SIZE];
	uint8_t					is_init;
}							t_infos;

# include "prototypes_malloc.h"

#endif
