/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes_malloc.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:14:59 by ezalos            #+#    #+#             */
/*   Updated: 2020/10/20 17:36:21 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_MALLOC_H
# define PROTOTYPES_MALLOC_H

int		main(int ac, char **av);
void	our_free(void *alloc);
void	*our_malloc(size_t size);
void	test_read(void *mem, size_t size);
void	test_write(void *mem, size_t size);

#endif
