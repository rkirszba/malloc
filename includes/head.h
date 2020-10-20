/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/20 20:56:34 by ezalos           ###   ########.fr       */
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

# define ZONE_SIZE	4096

# define ERROR		-1
# define SUCCESS	0

# define TRUE		1
# define FALSE		0

# define ZONE_TINY	1
# define ZONE_SMALL	2
# define ZONE_LARGE	3

# define PRINT_LINE_SIZE	32

# define ABS(x)		((x < 0) ? -x : x)

typedef	struct		s_alloc
{
	int32_t			size;
	uint8_t			*alloc;
}					t_alloc;

typedef	struct		s_zone_alloc
{
	void			*next_zone;
	t_alloc			allocation;
}					t_zone_alloc;

typedef	struct		s_malloc
{
	t_zone_alloc	*tiny_zone;
	size_t			tiny_zone_size;
	t_zone_alloc	*small_zone;
	size_t			small_zone_size;
}					t_malloc;

# include "prototypes_malloc.h"

#endif
