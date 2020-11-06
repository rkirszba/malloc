/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:45:12 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/05 14:37:38 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include <pthread.h>

// pthread_mutex_t lock;

t_infos			*static_mem(void)
{
	static t_infos		memory;
	// // int					thread_id;
	// //
	// // thread_id = pthread_self();
    // if (pthread_mutex_init(&lock, NULL) != 0)
    //     printf("\n mutex init failed\n");
	// else
	// {
	//     pthread_mutex_lock(&lock);
	//     pthread_mutex_unlock(&lock);
	//     pthread_mutex_destroy(&lock);
	// }
	return (&memory);
}
