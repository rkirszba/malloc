/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:45:12 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/21 12:46:55 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_malloc		**static_mem(void)
{
	static t_malloc		*memory;

	return (&memory);
}


t_malloc		*static_mem_test(void)
{
	static t_malloc		memory;

	return (&memory);
}
