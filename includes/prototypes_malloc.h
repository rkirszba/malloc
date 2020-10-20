/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_malloc.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:14:59 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/20 20:38:24 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_MALLOC_H
# define PROTOTYPES_MALLOC_H

int			main(int ac, char **av);
int8_t		malloc_exit(void);
int8_t		malloc_init(void);
void		our_free(void *alloc);
void		*our_malloc(size_t size);
t_malloc	**static_mem(void);
void		test_read(void *mem, size_t size);
void		test_write(void *mem, size_t size);
int8_t		zone_create(t_zone_alloc **zone, size_t zone_size);
int8_t		zone_all_liberate(t_zone_alloc *zone, size_t zone_size);
void		print_malloc_mem(void);

#endif
