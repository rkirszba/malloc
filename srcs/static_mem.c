/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:45:12 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/06 11:56:43 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_infos			*static_mem(void)
{
	static t_infos		memory;
	// // int					thread_id;
	// //
	// // thread_id = pthread_self();
	return (&memory);
}
