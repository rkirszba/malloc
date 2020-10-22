/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_malloc.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:14:59 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/22 15:18:51 by ldevelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_MALLOC_H
# define PROTOTYPES_MALLOC_H

t_alloc_header		*alloc_access_th(t_zone *zone, size_t zone_size,
			size_t umpteenth);
int8_t		alloc_split(t_alloc_header *alloc, size_t first_alloc_header_size);
int			main(int ac, char **av);
int8_t		malloc_exit(void);
int8_t		malloc_init(void);
int8_t		mem_index_add(t_alloc_header *availble_alloc);
uint8_t		mem_index_del(t_alloc_header *unavailble_alloc);
t_alloc_header		*mem_index_get(size_t size);
void 		mem_put_color(t_alloc_header *alloc, int8_t alloc_nb);
void		our_free(void *alloc);
void		*our_malloc(size_t size);
void		print_alloc_header(t_alloc_header *alloc, size_t *total_octet);
void		print_malloc_mem(void);
void		print_zone(t_zone *zone, size_t zone_size);
t_malloc	**static_mem(void);
void		test_read(void *mem, size_t size);
void		test_write(void *mem, size_t size);
int8_t		zone_create(t_zone **zone, size_t zone_size);
int8_t		zone_liberate_all(t_zone *zone, size_t zone_size);

void	alloc_header_init(t_alloc_header *header, size_t size,
		uint8_t available, uint8_t last);
void		*get_spot(size_t size_to_find);

#endif
