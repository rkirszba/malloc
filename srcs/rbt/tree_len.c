/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkirszba <rkirszba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:34:04 by rkirszba          #+#    #+#             */
/*   Updated: 2020/11/16 18:34:04 by rkirszba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

static int		count(t_rbt *rbt)
{
	(void)rbt;
	return (1);
}

int				tree_len(t_rbt *tree)
{
	return (tree_inorder(tree, count));
}
