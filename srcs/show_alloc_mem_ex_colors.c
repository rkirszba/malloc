/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem_ex_colors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezalos <ezalos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:31:24 by ezalos            #+#    #+#             */
/*   Updated: 2020/11/16 13:41:41 by ezalos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void			mem_put_color_header(int32_t alloc_nb)
{
	putstr("\x1b[48;2;30;30;0m");
	if (alloc_nb < 0)
	{
		alloc_nb = -(alloc_nb + 1);
		if (alloc_nb < (int)sizeof(t_rbt))
		{
			alloc_nb /= 8;
			if (alloc_nb % 2)
				putstr("\x1b[38;2;255;205;255m");
			else
				putstr("\x1b[38;2;205;255;255m");
		}
		else
		{
			alloc_nb /= 2;
			if (alloc_nb % 2)
				putstr("\x1b[38;2;255;255;155m");
			else
				putstr("\x1b[38;2;255;255;5m");
		}
	}
	else
		putstr("\x1b[38;2;105;55;255m");
}

int				mem_put_color(t_alloc_header *alloc, int32_t alloc_nb,
					int8_t header)
{
	if (header == TRUE)
		mem_put_color_header(alloc_nb);
	else
	{
		putstr("\x1b[48;2;0;0;60m");
		if (alloc->flags & HDR_AVAILABLE)
		{
			if (alloc_nb % 2)
				putstr("\x1b[38;2;155;255;155m");
			else
				putstr("\x1b[38;2;105;255;105m");
		}
		else
		{
			if (alloc_nb % 2)
				putstr("\x1b[38;2;255;105;105m");
			else
				putstr("\x1b[38;2;255;55;55m");
		}
	}
	return (1);
}
