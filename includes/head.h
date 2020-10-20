/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 11:15:02 by ldevelle          #+#    #+#             */
/*   Updated: 2020/10/20 17:32:15 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include <sys/mman.h>
# include <stddef.h>
# include <stddef.h>
# include <inttypes.h>
# include <stdlib.h>
# include <unistd.h>
# include "prototypes_malloc.h"

# define ZONE_SIZE	4096


typedef	struct		s_alloc
{
	int32_t			size;
	void			*alloc;
}					t_alloc;

typedef	struct		s_zone_alloc
{
	void			*next_zone;
	t_alloc			*allocation;
}					t_zone_alloc;

#endif
