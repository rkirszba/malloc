/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/11/16 13:05:14 by ezalos           ###   ########.fr       */
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
# define AVAILABLE_TABLE_SIZE		(SMALL_SIZE_MAX_FACTOR > \
TINY_SIZE_MAX_FACTOR ? SMALL_SIZE_MAX_FACTOR : TINY_SIZE_MAX_FACTOR) + 1
# define UNAVAILABLE_TABLE_SIZE		13

# include "malloc_structs.h"
# include "prototypes_malloc.h"

#endif
