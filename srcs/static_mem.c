/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:13:41 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:13:42 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

/*
**	#define		NB_THREAD  	8
**
**	t_infos			*static_mem(void)
**	{
**		static t_infos		memory[NB_THREAD];
**		static t_infos		memory;
**		int					thread_id;
**
**		thread_id = pthread_self();
**		return (&memory[thread_id % NB_THREAD]);
**		return (&memory);
**	}
*/

t_infos			*static_mem(void)
{
	static t_infos		memory;

	return (&memory);
}
