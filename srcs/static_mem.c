/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:45:12 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/06 17:17:59 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
// #define		NB_THREAD  8

t_infos			*static_mem(void)
{
	// static t_infos		memory[NB_THREAD];
	static t_infos		memory;
	// int					thread_id;

	// thread_id = pthread_self();
	// return (&memory[thread_id % NB_THREAD]);
	return (&memory);
}
