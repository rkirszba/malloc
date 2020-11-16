/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:11:35 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:11:36 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static uint8_t		flag_set(uint8_t flag, uint8_t category, uint8_t option)
{
	return (((~category) & flag) | (option & category));
}

uint8_t				flag_set_pos(uint8_t flag, uint8_t option)
{
	return (flag_set(flag, HDR_POS, option));
}

uint8_t				flag_set_type(uint8_t flag, uint8_t option)
{
	return (flag_set(flag, HDR_TYPE, option));
}

uint8_t				flag_set_availabilty(uint8_t flag, uint8_t option)
{
	return (flag_set(flag, HDR_AVAILABLE, option));
}
