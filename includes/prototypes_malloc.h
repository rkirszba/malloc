/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_malloc.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:14:59 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/21 12:22:23 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_MALLOC_H
# define PROTOTYPES_MALLOC_H

t_alloc		*alloc_access_th(t_zone *zone, size_t zone_size,
			size_t umpteenth);
int8_t		alloc_split(t_alloc *alloc, size_t first_alloc_size);
int			main(int ac, char **av);
int8_t		malloc_exit(void);
int8_t		malloc_init(void);
int8_t		mem_index_add(t_alloc *availble_alloc);
uint8_t		mem_index_del(t_alloc *unavailble_alloc);
t_alloc		*mem_index_get(size_t size);
void 		mem_put_color(t_alloc *alloc, int8_t alloc_nb);
void		our_free(void *alloc);
void		*our_malloc(size_t size);
void		print_alloc(t_alloc *alloc, size_t *total_octet,
			size_t alloc_nb);
void		print_malloc_mem(void);
void		print_zone(t_zone *zone, size_t zone_size);
t_malloc	**static_mem(void);
void		test_read(void *mem, size_t size);
void		test_write(void *mem, size_t size);
int8_t		zone_create(t_zone **zone, size_t zone_size);
int8_t		zone_liberate_all(t_zone *zone, size_t zone_size);

#endif
